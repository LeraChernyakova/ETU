#include "mandelbrot_cl.h"

#include <CL/cl.h>
#include <string>
#include <exception>
#include <fstream>
#include <sstream>

constexpr char kernelFile[] = "kernels/mandelbrot.cl";
constexpr char kernelFn[] = "calculate";

size_t Align( const size_t min, const size_t factor )
{
    return ( min + factor - 1 ) / factor * factor;
}

cl_context OclCreateContext( cl_device_id& device )
{
    cl_int rc = -30;

    cl_platform_id platform;
    clGetPlatformIDs( 1, &platform, nullptr );

    rc = clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 1, &device, nullptr );

    const cl_context_properties contextProperties[] = {
          CL_CONTEXT_PLATFORM, reinterpret_cast< cl_context_properties >( platform ), 0
    };

    cl_context context = clCreateContext( contextProperties, 1, &device, nullptr, nullptr, &rc );

    return context;
}


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

    rc = clBuildProgram( program, 1, &device, nullptr, nullptr, nullptr );

    kernel = clCreateKernel( program, kernelName.c_str(), &rc );

    return program;
}


Mandelbrot_CL::Mandelbrot_CL( size_t w, size_t h, size_t iterations )
    : Mandelbrot( w, h, iterations )
{}


void Mandelbrot_CL::Generate()
{
    constexpr size_t workGroupSize[ 2 ] = { 256, 1 };
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

    context = OclCreateContext( device );

    commandQueue = clCreateCommandQueueWithProperties( context, device, nullptr, &rc );

    buffer = clCreateBuffer( context, CL_MEM_WRITE_ONLY, dataSize, nullptr, &rc );

    program = OclCreateProgram( context, kernelFile, kernelFn, device, kernel );

    int iterations = static_cast< int >( iterations_ );
    int width = static_cast< int >( width_ );
    int height = static_cast< int >( height_ );

    clSetKernelArg( kernel, 0, sizeof( iterations ), &iterations );
    clSetKernelArg( kernel, 1, sizeof( width ), &width );
    clSetKernelArg( kernel, 2, sizeof( height ), &height );
    clSetKernelArg( kernel, 3, sizeof( buffer ), &buffer );

    clEnqueueNDRangeKernel(commandQueue, kernel, 2, nullptr, globalSize, workGroupSize, 0, nullptr, nullptr);

    clEnqueueReadBuffer( commandQueue, buffer, CL_TRUE, 0, dataSize, data.get(), 0, nullptr, nullptr );
    for ( size_t y = 0; y < height_; ++y )
    {
        for ( size_t x = 0; x < width_; ++x )
        {
            points_[ x + y * width_ ] = data[ x + y * globalSize[ 0 ] ];
        }
    }

    clReleaseKernel( kernel );
    clReleaseProgram( program );
    clReleaseMemObject( buffer );
    clReleaseCommandQueue( commandQueue );
    clReleaseContext( context );
}
