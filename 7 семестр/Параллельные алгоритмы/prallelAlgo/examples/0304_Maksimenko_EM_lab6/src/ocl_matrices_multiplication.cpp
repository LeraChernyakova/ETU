#include "ocl_matrices_multiplication.h"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

#define OCL_CHECK_RC( rc ) { ocl::OclMatricesMultiplication::process_rc( ( rc ), __FILE__, __LINE__ ); }

namespace ocl
{

OclMatricesMultiplication::OclMatricesMultiplication()
    : initialized_{ false }
{} // OclMatricesMultiplication


OclMatricesMultiplication::~OclMatricesMultiplication()
{
    deinit();
} // ~OclMatricesMultiplication


void OclMatricesMultiplication::process_rc( cl_int rc, const std::string& filename, size_t line )
{
    if ( CL_SUCCESS == rc )
    {
        return;
    }

    throw std::runtime_error{ "OpenCL error " + std::to_string( rc )
                            + " at " + filename + " : " + std::to_string( line ) };
} // process_rc


bool OclMatricesMultiplication::init( const size_t lhs_w, const size_t common_size, const size_t rhs_h
                                    , int32_t* lhs_data, int32_t* rhs_data )
{
    const int32_t lhs_w_aligned = align( lhs_w, local_work_size_[ 0 ] );
    const int32_t common_size_aligned = align( common_size, local_work_size_[ 1 ] );
    const int32_t rhs_h_aligned = align( rhs_h, local_work_size_[ 1 ] );

    const size_t lhs_aligned_size = lhs_w_aligned * common_size_aligned;
    const size_t rhs_aligned_size = common_size_aligned * rhs_h_aligned;
    const size_t res_aligned_size = lhs_w_aligned * rhs_h_aligned;

    global_work_size_[ 0 ] = lhs_w_aligned;
    global_work_size_[ 1 ] = rhs_h_aligned;
    real_data_size_[ 0 ]   = lhs_w;
    real_data_size_[ 1 ]   = rhs_h;

    std::unique_ptr< int32_t[] > lhs_aligned = std::make_unique< int32_t[] >( lhs_aligned_size );
    std::unique_ptr< int32_t[] > rhs_aligned = std::make_unique< int32_t[] >( rhs_aligned_size );

    for ( size_t y = 0; y < common_size; ++y )
    {
        for ( size_t x = 0; x < lhs_w; ++x )
        {
            lhs_aligned[ x + y * lhs_w_aligned ] = lhs_data[ x + y * lhs_w ];
        }
    }
    for ( size_t y = 0; y < rhs_h; ++y )
    {
        for ( size_t x = 0; x < common_size; ++x )
        {
            rhs_aligned[ x + y * common_size_aligned ] = rhs_data[ x + y * common_size ];
        }
    }

    deinit();
    try
    {
        create_context();
        create_command_queue();
        buffers_.push_back( create_buffer( CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
                                         , lhs_aligned_size * sizeof( int32_t ), lhs_aligned.get() ) );
        buffers_.push_back( create_buffer( CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
                                         , rhs_aligned_size * sizeof( int32_t ), rhs_aligned.get() ) );
        buffers_.push_back( create_buffer( CL_MEM_WRITE_ONLY, res_aligned_size * sizeof( int32_t ) ) );
        create_program( "multiplication.cl", "multiply" );
        OCL_CHECK_RC( clSetKernelArg( kernel_, 0, sizeof( lhs_w_aligned ), &lhs_w_aligned ) );
        OCL_CHECK_RC( clSetKernelArg( kernel_, 1, sizeof( common_size_aligned ), &common_size_aligned ) );
        OCL_CHECK_RC( clSetKernelArg( kernel_, 2, sizeof( rhs_h_aligned ), &rhs_h_aligned ) );
        OCL_CHECK_RC( clSetKernelArg( kernel_, 3, sizeof( buffers_[ 0 ] ), &buffers_[ 0 ] ) );
        OCL_CHECK_RC( clSetKernelArg( kernel_, 4, sizeof( buffers_[ 1 ] ), &buffers_[ 1 ] ) );
        OCL_CHECK_RC( clSetKernelArg( kernel_, 5, sizeof( buffers_[ 2 ] ), &buffers_[ 2 ] ) );
        initialized_ = true;
    }
    catch ( const std::exception& e )
    {
        std::cerr << "Failed to initialize: " << e.what() << '\n';
        deinit();
    }
    return initialized_;
} // init


void OclMatricesMultiplication::deinit()
{
    if ( kernel_ )
    {
        clReleaseKernel( kernel_ );
        kernel_ = 0;
    }
    if ( program_ )
    {
        clReleaseProgram( program_ );
        program_ = 0;
    }
    for ( cl_mem buffer: buffers_ )
    {
        clReleaseMemObject( buffer );
    }
    buffers_.clear();
    if ( command_queue_ )
    {
        clReleaseCommandQueue( command_queue_ );
        command_queue_ = 0;
    }
    if ( context_ )
    {
        clReleaseContext( context_ );
        context_ = 0;
    }
    initialized_ = false;
} // deinit


void OclMatricesMultiplication::create_context()
{
    cl_int rc;
    cl_platform_id platform;

    OCL_CHECK_RC( clGetPlatformIDs( 1, &platform, nullptr ) );
    rc = clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 1, &device_, nullptr );
    if ( CL_SUCCESS != rc )
    {
        std::cerr << "No GPU found (error code: " << rc << "). Trying to use CPU\n";
        OCL_CHECK_RC( clGetDeviceIDs( platform, CL_DEVICE_TYPE_CPU, 1, &device_, nullptr ) );
    }

    const cl_context_properties context_properties[] = {
          CL_CONTEXT_PLATFORM, reinterpret_cast< cl_context_properties >( platform )
        , 0
    };
    context_ = clCreateContext( context_properties, 1, &device_, nullptr, nullptr, &rc );
    OCL_CHECK_RC( rc );
} // create_context


void OclMatricesMultiplication::create_command_queue()
{
    cl_int rc;

    command_queue_ = clCreateCommandQueueWithProperties( context_, device_, nullptr, &rc );
    OCL_CHECK_RC( rc );
} // create_command_queue


cl_mem OclMatricesMultiplication::create_buffer( cl_mem_flags mem_flags, size_t mem_size, void* host_ptr )
{
    cl_int rc;
    cl_mem buffer = clCreateBuffer( context_, mem_flags, mem_size, host_ptr, &rc );
    OCL_CHECK_RC( rc );
    return buffer;
} // create_buffer


void OclMatricesMultiplication::create_program( const std::string& file, const std::string& kernel_name )
{
    cl_int rc;

    std::ifstream file_stream{ file };
    std::stringstream source_code_buffer;
    source_code_buffer << file_stream.rdbuf();
    const std::string source_code_str{ source_code_buffer.str() };
    const char* source_code = source_code_str.c_str();
    const size_t source_code_length = source_code_str.length();

    program_ = clCreateProgramWithSource( context_, 1, &source_code, &source_code_length, &rc );
    OCL_CHECK_RC( rc );

    rc = clBuildProgram( program_, 1, &device_, nullptr, nullptr, nullptr );
    if ( CL_SUCCESS != rc )
    {
        size_t build_log_size = 0;
        clGetProgramBuildInfo( program_, device_, CL_PROGRAM_BUILD_LOG, 0, nullptr, &build_log_size );
        std::string build_log;
        build_log.resize( build_log_size, '0' );
        clGetProgramBuildInfo( program_, device_, CL_PROGRAM_BUILD_LOG, build_log_size, build_log.data(), nullptr );
        std::cerr << "Build log (size: " << build_log_size << "): " << build_log << '\n';
        OCL_CHECK_RC( rc );
    }

    kernel_ = clCreateKernel( program_, kernel_name.c_str(), &rc );
    OCL_CHECK_RC( rc );
} // create_program


std::unique_ptr< int32_t[] > OclMatricesMultiplication::process()
{
    if ( !initialized_ )
    {
        std::cerr << "Not initialized\n";
        return nullptr;
    }

    const size_t buffer_size     = global_work_size_[ 0 ] * global_work_size_[ 1 ] * sizeof( int32_t );
    const size_t ret_buffer_size = real_data_size_[ 0 ]   * real_data_size_[ 1 ]   * sizeof( int32_t );
    std::unique_ptr< int32_t[] > buffer{ std::make_unique< int32_t[] >( buffer_size ) };
    std::unique_ptr< int32_t[] > ret_buffer{ std::make_unique< int32_t[] >( ret_buffer_size ) };
    try
    {
        OCL_CHECK_RC( clEnqueueNDRangeKernel(
              command_queue_
            , kernel_
            , 2
            , nullptr
            , global_work_size_
            , local_work_size_
            , 0
            , nullptr
            , nullptr
        ) );

        OCL_CHECK_RC( clEnqueueReadBuffer( command_queue_, buffers_[ 2 ], CL_TRUE
                                         , 0, buffer_size, buffer.get(), 0, nullptr, nullptr ) );
        for ( size_t y = 0; y < real_data_size_[ 1 ]; ++y )
        {
            for ( size_t x = 0; x < real_data_size_[ 0 ]; ++x )
            {
                ret_buffer[ x + y * real_data_size_[ 0 ] ] = buffer[ x + y * global_work_size_[ 0 ] ];
            }
        }
    }
    catch( const std::exception& e )
    {
        std::cerr << "Run failed: " << e.what() << '\n';
    }
    return ret_buffer;
} // process


size_t OclMatricesMultiplication::align( const size_t size, const size_t base )
{
    return ( size + base - 1 ) / base * base;
}


} // namespace ocl
