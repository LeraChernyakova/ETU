#include <string>
#include <iostream>
#include <CL/cl.h>
#include <sstream>
#include <vector>
#include "utilities/utils.h"
#include "utilities/assert.h"

class OpenCLEngine {
private:
    cl_device_id device;
    cl_context ctx;
    cl_command_queue queue;
    cl_kernel kernel;
    cl_program program;

    cl_mem first_buffer = nullptr;
    cl_mem second_buffer = nullptr;
    cl_mem result_buffer = nullptr;

    // Get device
    static cl_device_id get_device(bool strict_cpu=false) {
        cl_uint platform_count{0};
        cl(clGetPlatformIDs(0, nullptr, &platform_count));

        std::vector<cl_platform_id> platforms(platform_count);
        cl(clGetPlatformIDs(platform_count, platforms.data(), nullptr));

        for (cl_platform_id platform_id : platforms) {
            cl_uint device_count{0};
            cl(clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, nullptr, &device_count));

            if (device_count == 0)
                continue;

            std::vector<cl_device_id> devices(device_count);
            cl(clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 1, devices.data(), nullptr));

            // Check if we strictly need CPU for calculations
            // (for example if there are also GPU on the computer)
            if (!strict_cpu) {
                log_device_info(devices.at(0));
                return devices.at(0);
            } else {
                cl_device_type device_type;
                for (cl_device_id iter_device: devices) {
                    cl(clGetDeviceInfo(iter_device, CL_DEVICE_TYPE, sizeof(cl_device_type), &device_type, nullptr));

                    if (device_type == CL_DEVICE_TYPE_CPU) {
                        log(to_string(iter_device));
                        log_device_info(iter_device);
                        return iter_device;
                    }
                }
                continue;
            }
        }
        return nullptr;
    };


    void build(std::string source) {
        cl_int err;

        const char* string = source.data();
        const size_t length = source.size();

        program = clCreateProgramWithSource(ctx, 1, &string, &length, &err);
        cl_ok(err);
        
        const char* options = "";
        err = clBuildProgram(program, 1, &device, options, nullptr, nullptr);
        cl_ok(err);

        if (err == CL_BUILD_PROGRAM_FAILURE) {
            log("test");
            size_t value_size;
            cl(clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &value_size));

            std::vector<unsigned char> value;
            cl(clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, value_size, value.data(), nullptr));

            throw std::runtime_error("Failed to build the program: " + to_string(value.data()));
        }
    };

public:
    void init(bool strict_cpu = false) {
        cl_int err;

        // Defining using device
        device = get_device(strict_cpu);

        // Creating context - the environment in which kernel will execute (Here we only specify that only 1 device will be used)
        ctx = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &err);

        // Creating command queue for one device in specified context
        queue = clCreateCommandQueueWithProperties(ctx, device, nullptr, &err);
        cl_ok(err);
    }


    void load_program(std::string source, std::string kernel_name) {
        cl_int err;

        // Building program
        build(std::move(source));

        // Creating kernel with compiled program and specified name
        kernel = clCreateKernel(program, kernel_name.data(), &err);
        cl_ok(err);
    }


    void create_buffers(size_t size, std::vector<int>& first_buffer_data, std::vector<int>& second_buffer_data, size_t work_group_width, size_t work_group_height) {
        cl_int err = 0;

        first_buffer = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * size * size, first_buffer_data.data(), &err);
        cl_ok(err);

        second_buffer = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * size * size, second_buffer_data.data(), &err);
        cl_ok(err);

        result_buffer = clCreateBuffer(ctx, CL_MEM_READ_WRITE, sizeof(int) * size * size, nullptr, &err);
        cl_ok(err);

        int sizeInt = size;

        // Linking it with the kernel
        cl(clSetKernelArg(kernel, 0, sizeof(cl_mem), &result_buffer));
        cl(clSetKernelArg(kernel, 1, sizeof(cl_mem), &first_buffer));
        cl(clSetKernelArg(kernel, 2, sizeof(cl_mem), &second_buffer));
        cl(clSetKernelArg(kernel, 3, sizeof(int), &sizeInt));

        // Enqueueing kernel for execution with specifying index range parameters such as:
        //      * Global work size - size of index range as a whole
        //      * Local work size - size of work-groups that divide global space. Work items in groups execute concurrently
        size_t global[2] = {size, size};
        size_t local[2] = {work_group_width, work_group_height};
        cl(clEnqueueNDRangeKernel(queue, kernel, 2, nullptr, global, local, 0, nullptr, nullptr));
    }


    void read_buffer(int* result, size_t size) {
        // Enqueueing image read
        cl(clEnqueueReadBuffer(queue, result_buffer, CL_TRUE,
                               0, sizeof(int) * size * size, result,
                               0, nullptr, nullptr));
    }


    void execute_and_wait() {
        // Submitting commands in queue for the execution
        cl(clFlush(queue));

        // Blocking until all prev. enqueued commands in the command queue have completed
        cl(clFinish(queue));
    }


    void clean_up() {
        cl(clReleaseKernel(kernel));
        cl(clReleaseProgram(program));
        cl(clReleaseMemObject(first_buffer));
        cl(clReleaseMemObject(second_buffer));
        cl(clReleaseMemObject(result_buffer));

        cl(clReleaseCommandQueue(queue));
        cl(clReleaseContext(ctx));
    }
};