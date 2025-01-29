#ifndef OPENCLHANDLER
#define OPENCLHANDLER

#include "defines.hpp"

#include <iostream>
#include <vector>
#include <CL/cl.h>

#include "utility.hpp"

class OpenCLWorker {
    private:
        cl_device_id device;
        cl_context context;
        cl_program program;
        cl_kernel kernel;
        cl_command_queue queue;

    private:
        // Инициализация.
        cl_device_id create_device(int platform_ind);
        cl_context create_context(cl_device_id device);
        cl_program build_program(cl_context context, cl_device_id device);
        cl_command_queue create_queue(cl_context context, cl_device_id device);
        cl_kernel create_kernel(cl_program program);

    public:
        OpenCLWorker(bool discreate_gpu);
        ~OpenCLWorker();

        // Работа с ядром.
        cl_mem create_buffer(cl_mem_flags flags, size_t size, void* host_ptr);
        void fill_buffer(cl_mem buffer, cl_bool blocking_read, size_t size, void* res_ptr);
        void read_buffer(cl_mem buffer, cl_bool blocking_read, size_t size, void* res_ptr);
        void release_buffer(cl_mem buffer);

        void set_kernel_arg(uint arg_ind, size_t arg_size, const void* argument);
        void send_to_execution(cl_uint work_dim, const size_t* global_work_size, const size_t* local_work_size);
        void wait_completion();
};

#endif