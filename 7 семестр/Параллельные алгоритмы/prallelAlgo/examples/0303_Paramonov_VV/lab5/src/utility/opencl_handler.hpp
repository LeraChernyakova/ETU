#define PROGRAM_FILE "mandelbrot.cl"
#define KERNEL_FUNC "mandelbrot"
#define CL_TARGET_OPENCL_VERSION 300

#include <iostream>
#include <vector>
#include <CL/cl.h>

#include "utility.hpp"


// Инициализация.
cl_device_id create_device(int platform_ind);
cl_context create_context(cl_device_id device);
cl_program build_program(cl_context context, cl_device_id device);
cl_mem create_buffer(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr);
void fill_buffer(cl_command_queue queue, cl_mem buffer, cl_bool blocking_read, 
                        size_t size, void* res_ptr);
cl_command_queue create_queue(cl_context context, cl_device_id device);
cl_kernel create_kernel(cl_program program);

// Работа с ядром.
void set_kernel_arg(cl_kernel kernel, uint arg_ind, size_t arg_size, const void* argument);
void send_to_execution(cl_command_queue queue, cl_kernel kernel, cl_uint work_dim, 
                        const size_t* global_work_size, const size_t* local_work_size);
void read_result_from_buf(cl_command_queue queue, cl_mem buffer, cl_bool blocking_read, 
                        size_t size, void* res_ptr);

