#include <cl_matr.h>

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>

#include <matrix.h>
#include <CL/cl.h>

namespace
{

constexpr char kernel_file[] = "matrix.cl";
constexpr char main_func[] = "matrix";


cl_context create_ocl_context()
{
     cl_device_id device;
     cl_platform_id platform;
     cl_context context;

     if ( clGetPlatformIDs( 1, &platform, nullptr ) )
     {
          throw std::runtime_error{ "Cannot get platform for OpenCL" };
     }

     cl_int ret = clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 1, &device, nullptr );
	if ( ret )
     {
          std::cerr << "Cannot get GPUs for OpenCL, using CPUs (code " << ret << ")\n";
          ret = clGetDeviceIDs( platform, CL_DEVICE_TYPE_CPU, 1, &device, nullptr );
          if ( ret )
          {
               throw std::runtime_error{ "Cannot get CPUs for OpenCL (" + std::to_string( ret ) + ')' };
          }
     }

     cl_context_properties props[] = { CL_CONTEXT_PLATFORM, reinterpret_cast< cl_context_properties >( platform ), 0 };
     context = clCreateContext( props, 1, &device, nullptr, nullptr, &ret );
     if ( ret )
     {
          throw std::runtime_error{ "Cannot create OpenCL context (" + std::to_string( ret ) + ')' };
     }
     return context;
}


cl_mem create_ocl_buffer( cl_context context, void *data, size_t size, cl_mem_flags flags )
{
     cl_int err = 0;
     cl_mem buffer = clCreateBuffer( context, flags, size, data, &err );
     if ( err )
     {
          throw std::runtime_error{ "Cannot create OpenCL buffer" };
     }
     return buffer;
}


cl_kernel create_ocl_kernel( cl_context context, const std::string& filename,
     const std::string& func, cl_device_id device )
{
     std::ifstream file{ filename };
     if ( !file )
     {
          throw std::runtime_error{ "Cannot open OpenCL kernel file: " + filename };
     }
     std::stringstream data;
     data << file.rdbuf();
     std::string content{ data.str() };
     const char *raw_ptr = content.c_str();

     cl_program prog;
     cl_int err;

     prog = clCreateProgramWithSource( context, 1, &raw_ptr, nullptr, &err );
     if ( err )
     {
          throw std::runtime_error{ "Cannot create OpenCL program with source" };
     }
     err = clBuildProgram( prog, 1, &device, nullptr, nullptr, nullptr );
     if ( err )
     {
          size_t log_size = 0;
          clGetProgramBuildInfo( prog, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size );
          std::vector< char > log( log_size );
          clGetProgramBuildInfo( prog, device, CL_PROGRAM_BUILD_LOG, log_size, log.data(), NULL );
          std::cerr << log.data() << std::endl;
          throw std::runtime_error{ "Cannot build OpenCL program (" + std::to_string( err ) + ')' };
     }
     cl_kernel kernel = clCreateKernel( prog, func.c_str(), &err );
     if ( err )
     {
          throw std::runtime_error{ "Cannot create OpenCL kernel" };
     }
     clReleaseProgram( prog );
     return kernel;
}


void print_device_info( cl_device_id id )
{
     constexpr size_t max_name_len = 1024;
     cl_int err;
     cl_char vendor_name[ max_name_len ] = { 0 };
     cl_char device_name[ max_name_len ] = { 0 };
     err = clGetDeviceInfo( id, CL_DEVICE_VENDOR, sizeof( vendor_name ), vendor_name, nullptr );
     err |= clGetDeviceInfo( id, CL_DEVICE_NAME, sizeof( device_name ), device_name, nullptr );
     if ( err )
     {
          throw std::runtime_error{ "Cannot get device info from OpenCL context" };
     }
     std::cerr << "Device " << id << ": " << vendor_name << " " << device_name << '\n';
}

} // anonymous namespace


Matrix multiply_matrices_ocl( const Matrix& lhs, const Matrix& rhs )
{
     size_t rows = lhs.get_rows();
     size_t cols = rhs.get_cols();
     Matrix result( rows, cols );

     cl_kernel kernel;
     cl_context context;
     cl_command_queue cmd_queue;
     cl_device_id device;
     cl_int err = 0;
     cl_mem buffer_lhs, buffer_rhs, buffer_result;

     context = create_ocl_context();

     if ( clGetContextInfo( context, CL_CONTEXT_DEVICES, sizeof( cl_device_id ), &device, nullptr ) )
     {
          throw std::runtime_error{ "Cannot get OpenCL context info" };
     }

     print_device_info( device );
     cmd_queue = clCreateCommandQueueWithProperties( context, device, nullptr, &err );
     if ( err )
     {
          throw std::runtime_error{ "Cannot create OpenCL command queue" };
     }

     buffer_lhs = create_ocl_buffer( context, ( void* )lhs.data(), rows * cols * sizeof( float ),
          CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR );
     buffer_rhs = create_ocl_buffer( context, ( void* )rhs.data(), rows * cols * sizeof( float ),
          CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR );
     buffer_result = create_ocl_buffer( context, nullptr, rows * cols * sizeof( float ),
          CL_MEM_WRITE_ONLY );

     kernel = create_ocl_kernel( context, kernel_file, main_func, device );

     if ( clSetKernelArg( kernel, 0, sizeof( buffer_lhs ), &buffer_lhs )
          || clSetKernelArg( kernel, 1, sizeof( buffer_rhs ), &buffer_rhs )
          || clSetKernelArg( kernel, 2, sizeof( buffer_result ), &buffer_result ) )
     {
          throw std::runtime_error{ "Cannot set OpenCL kernel argument" };
     }
     size_t device_work_size[ 2 ] = { rows, cols };
     size_t device_offset[ 2 ] = { 0, 0 };
     if ( clEnqueueNDRangeKernel( cmd_queue, kernel, 2, device_offset,
                                  device_work_size, local_work_size, 0, nullptr, nullptr ) )
     {
          throw std::runtime_error{ "Cannot enqueue OpenCL calculation command" };
     }
     if ( clEnqueueReadBuffer( cmd_queue, buffer_result, CL_TRUE, 0,
          rows * cols * sizeof( float ),
          result.data(), 0, nullptr, nullptr) )
     {
          throw std::runtime_error{ "Cannot enqueue OpenCL read command" };
     }

     clFinish( cmd_queue );

     clReleaseMemObject( buffer_lhs );
     clReleaseMemObject( buffer_rhs );
	clReleaseMemObject( buffer_result );
     clReleaseCommandQueue( cmd_queue );
     clReleaseContext( context );
     return result;
}
