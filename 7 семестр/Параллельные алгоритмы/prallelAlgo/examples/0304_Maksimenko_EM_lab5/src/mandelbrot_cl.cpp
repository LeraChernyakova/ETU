#include "mandelbrot_cl.h"

#include <CL/cl.h>
#include <string>
#include <exception>
#include <fstream>
#include <sstream>

namespace // anonymous
{

constexpr char kernelFile[] = "kernels/mandelbrot.cl";
constexpr char kernelFn[] = "calculate";


size_t Align( const size_t min, const size_t factor )
{
    return ( min + factor - 1 ) / factor * factor;
} // Align


void OclProcessRc( cl_int rc, const std::string& filename, size_t line )
{
    if ( CL_SUCCESS == rc )
        return;

    throw std::runtime_error{ "OpenCL error " + std::to_string( rc )
                             + " at " + filename + ":" + std::to_string( line ) };
} // OclProcessRc


#define OCL_CHECK_RC( rc ) OclProcessRc( rc, __FILE__, __LINE__ );


cl_context OclCreateContext( cl_device_id& device )
{
    cl_int rc = -30;

    cl_platform_id platform;
    OCL_CHECK_RC( clGetPlatformIDs( 1, &platform, nullptr ) );

    rc = clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 1, &device, nullptr );
    if ( CL_SUCCESS != rc )
    {
        std::cerr << "No GPU found (error code: " << rc << "). Trying to use CPU\n";
        OCL_CHECK_RC( clGetDeviceIDs( platform, CL_DEVICE_TYPE_CPU, 1, &device, nullptr ) );
    }

    const cl_context_properties contextProperties[] = {
          CL_CONTEXT_PLATFORM, reinterpret_cast< cl_context_properties >( platform )
        , 0
    };

    cl_context context = clCreateContext( contextProperties, 1, &device, nullptr, nullptr, &rc );
    OCL_CHECK_RC( rc );

    return context;
} // OclCreateContext


cl_program OclCreateProgram(
    cl_context context
    , const std::string& file
    , const std::string& kernelName
    , const cl_device_id device
    , cl_kernel& kernel )
{
    cl_int rc;

    std::ifstream fileStream( file );
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    const std::string sourceCode{ buffer.str() };
    const char* sourceCodePtr = sourceCode.c_str();
    const size_t sourceCodeLength{ sourceCode.length() };

    cl_program program = clCreateProgramWithSource( context, 1, &sourceCodePtr, &sourceCodeLength, &rc );
    OCL_CHECK_RC( rc );

    rc = clBuildProgram( program, 1, &device, nullptr, nullptr, nullptr );
    if ( CL_SUCCESS != rc )
    {
        size_t buildLogSize = 0;
        clGetProgramBuildInfo( program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &buildLogSize );
        std::vector< char > buildLog( buildLogSize );
        clGetProgramBuildInfo( program, device, CL_PROGRAM_BUILD_LOG, buildLogSize, buildLog.data(), NULL );
        std::cerr << buildLog.data() << std::endl;
        OCL_CHECK_RC( rc );
    }

    kernel = clCreateKernel( program, kernelName.c_str(), &rc );
    OCL_CHECK_RC( rc );

    return program;
} // OclCreateProgram

} // anonymous namespace


MandelbrotCl::MandelbrotCl( size_t w, size_t h, size_t iterations )
    : Mandelbrot( w, h, iterations )
{} // MandelbrotCl


void MandelbrotCl::Generate()
{
    constexpr size_t workGroupSize[ 2 ] = { 128, 1 };
    const size_t globalSize[ 2 ] = { Align( width_, workGroupSize[ 0 ] ), Align( height_, workGroupSize[ 1 ] ) };
    const size_t dataSize = globalSize[ 0 ] * globalSize[ 1 ];
    std::unique_ptr< uint8_t[] > data = std::make_unique< uint8_t[] >( dataSize );

    cl_int rc;
    cl_device_id device;
    cl_context context;
    cl_command_queue commandQueue;
    cl_mem buffer;
    cl_program program;
    cl_kernel kernel;

    try
    {
        context = OclCreateContext( device );

        commandQueue = clCreateCommandQueueWithProperties( context, device, nullptr, &rc );
        OCL_CHECK_RC( rc );

        buffer = clCreateBuffer( context, CL_MEM_WRITE_ONLY, dataSize, nullptr, &rc );
        OCL_CHECK_RC( rc );

        program = OclCreateProgram( context, kernelFile, kernelFn, device, kernel );

        int iterations = static_cast< int >( iterations_ );
        int width = static_cast< int >( width_ );
        int height = static_cast< int >( height_ );

        OCL_CHECK_RC( clSetKernelArg( kernel, 0, sizeof( iterations ), &iterations ) );
        OCL_CHECK_RC( clSetKernelArg( kernel, 1, sizeof( width ), &width ) );
        OCL_CHECK_RC( clSetKernelArg( kernel, 2, sizeof( height ), &height ) );
        OCL_CHECK_RC( clSetKernelArg( kernel, 3, sizeof( buffer ), &buffer ) );

        OCL_CHECK_RC( clEnqueueNDRangeKernel(
            commandQueue
            , kernel
            , 2
            , nullptr
            , globalSize
            , workGroupSize
            , 0
            , nullptr
            , nullptr
        ) );

        OCL_CHECK_RC( clEnqueueReadBuffer( commandQueue, buffer, CL_TRUE
                                         , 0, dataSize, data.get(), 0, nullptr, nullptr ) );
        for ( size_t y = 0; y < height_; ++y )
        {
            for ( size_t x = 0; x < width_; ++x )
            {
                points_[ x + y * width_ ] = data[ x + y * globalSize[ 0 ] ];
            }
        }

        OCL_CHECK_RC( clReleaseKernel( kernel ) );
        OCL_CHECK_RC( clReleaseProgram( program ) );
        OCL_CHECK_RC( clReleaseMemObject( buffer ) );
        OCL_CHECK_RC( clReleaseCommandQueue( commandQueue ) );
        OCL_CHECK_RC( clReleaseContext( context ) );
    }
    catch ( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
    }
} // Generate
