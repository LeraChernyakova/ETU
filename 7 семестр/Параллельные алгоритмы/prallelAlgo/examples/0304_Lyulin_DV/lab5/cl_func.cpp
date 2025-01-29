#include <cl_func.h>

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

#include <CL/cl.h>

namespace
{

constexpr size_t max_dev_count = 16;
constexpr char kernel_file[] = "mandelbrot.cl";
constexpr char main_func[] = "mandelbrot";


cl_context create_ocl_context( cl_uint& num_devices )
{
     std::array< cl_device_id, max_dev_count > devices;
     cl_platform_id platform;
     cl_context context;

     if ( clGetPlatformIDs( 1, &platform, nullptr ) )
     {
          throw std::runtime_error{ "Cannot get platform for OpenCL" };
     }

     cl_int ret = clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, max_dev_count, devices.data(), &num_devices );
	if ( ret )
     {
          std::cerr << "Cannot get GPUs for OpenCL, using CPUs (code " << ret << ")\n";
          ret = clGetDeviceIDs( platform, CL_DEVICE_TYPE_CPU, max_dev_count, devices.data(), &num_devices );
          if ( ret )
          {
               throw std::runtime_error{ "Cannot get CPUs for OpenCL (" + std::to_string( ret ) + ')' };
          }
     }

     cl_context_properties props[] = { CL_CONTEXT_PLATFORM, reinterpret_cast< cl_context_properties >( platform ), 0 };
     context = clCreateContext( props, num_devices, devices.data(), nullptr, nullptr, &ret );
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


cl_kernel create_ocl_kernel( cl_context context, const std::string& filename, const std::string& func,
     const cl_device_id *device_list, size_t num_devices )
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
     err = clBuildProgram( prog, num_devices, device_list, nullptr, nullptr, nullptr );
     if ( err )
     {
          size_t log_size = 0;
          clGetProgramBuildInfo( prog, device_list[ 0 ], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size );
          std::vector< char > log( log_size );
          clGetProgramBuildInfo( prog, device_list[ 0 ], CL_PROGRAM_BUILD_LOG, log_size, log.data(), NULL );
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


void mandelbrot_ocl_calc( uint8_t *data, size_t width, size_t height, size_t channels )
{
     cl_kernel kernel;
     cl_context context;
     std::array< cl_command_queue, max_dev_count > cmd_queue;
     std::array< cl_device_id, max_dev_count > devices;
     cl_uint num_devices = 0;
     cl_int err = 0;
     cl_mem buffer;

     context = create_ocl_context( num_devices );

     if ( clGetContextInfo( context, CL_CONTEXT_DEVICES,
          sizeof( cl_device_id ) * max_dev_count, devices.data(), nullptr ) )
     {
          throw std::runtime_error{ "Cannot get OpenCL context info" };
     }

     for ( size_t i = 0; i < num_devices; i++ )
     {
          print_device_info( devices[ i ] );
          cmd_queue[ i ] = clCreateCommandQueueWithProperties( context, devices[ i ], nullptr, &err );
          if ( err )
          {
               throw std::runtime_error{ "Cannot create OpenCL command queue" };
          }
     }

     buffer = create_ocl_buffer( context, nullptr, width * height * channels, CL_MEM_WRITE_ONLY );
     kernel = create_ocl_kernel( context, kernel_file, main_func, devices.data(), num_devices );

     if ( clSetKernelArg( kernel, 0, sizeof( buffer ), &buffer ) )
     {
          throw std::runtime_error{ "Cannot set OpenCL kernel argument" };
     }

     size_t device_work_size[ 2 ] = { width, height / num_devices };
     for ( size_t i = 0; i < num_devices; i++ )
     {
          size_t device_work_offset[ 2 ] = { 0, device_work_size[ 1 ] * i };
          size_t offset = device_work_offset[ 1 ] * channels * width;
          if ( clEnqueueNDRangeKernel( cmd_queue[ i ], kernel, 2, device_work_offset,
                                        device_work_size, local_work_size, 0, nullptr, nullptr ) )
          {
               throw std::runtime_error{ "Cannot enqueue OpenCL calculation command" };
          }
          if ( clEnqueueReadBuffer( cmd_queue[ i ], buffer, CL_FALSE, offset,
               width * height * channels / num_devices,
               data, 0, nullptr, nullptr) )
          {
               throw std::runtime_error{ "Cannot enqueue OpenCL read command" };
          }
     }
     for( size_t i = 0; i < num_devices; i++ )
     {
          clFinish( cmd_queue[ i ] );
     }

	clReleaseMemObject( buffer );
     for ( size_t i = 0; i < num_devices; i++)
     {
          clReleaseCommandQueue( cmd_queue[ i ] );
     }
     clReleaseContext( context );
}
