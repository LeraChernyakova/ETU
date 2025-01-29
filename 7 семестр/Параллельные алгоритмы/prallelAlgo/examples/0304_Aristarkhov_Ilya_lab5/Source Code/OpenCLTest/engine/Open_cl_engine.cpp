//
// Created by ilya201232 on 04.11.23.
//

#include <utility>
#include <vector>
#include <iostream>

#include "Open_cl_engine.h"
#include "../assert/assert_cl.h"

void Open_cl_engine::init() {
    cl_int err;

    device = get_device();

    // Creating context - the environment in which kernel will execute (Here we only specify that only 1 device will be used)
    ctx = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &err);
    cl_ok(err);

    // Creating command queue for one device in specified context
    queue = clCreateCommandQueueWithProperties(ctx, device, nullptr, &err);
    cl_ok(err);
}

void Open_cl_engine::load_program(std::string source, std::string kernel_name) {
    cl_int err;

    // Building program
    build(std::move(source));

    // Creating kernel with compiled program and specified name
    kernel = clCreateKernel(program, kernel_name.data(), &err);
    cl_ok(err);
}

void Open_cl_engine::create_img(size_t width, size_t height) {
    cl_int err;

    cl_image_format format;
    format.image_channel_order = CL_RGBA;
    format.image_channel_data_type = CL_UNSIGNED_INT8;

    cl_image_desc desc;
    desc.image_type = CL_MEM_OBJECT_IMAGE2D;
    desc.image_width = width;
    desc.image_height = height;
    desc.image_depth = 0;
    desc.image_array_size = 0;
    desc.image_row_pitch = 0;
    desc.image_slice_pitch = 0;
    desc.num_mip_levels = 0;
    desc.num_samples = 0;
    desc.buffer = nullptr;

    // Creating image
    cl_img = clCreateImage(ctx, CL_MEM_WRITE_ONLY, &format, &desc, nullptr, &err);
    cl_ok(err);

    // Linking it with the kernel
    cl(clSetKernelArg(kernel, 0, sizeof(cl_img), &cl_img));

    // Enqueueing kernel for execution with specifying index range parameters such as:
    //      * Global work size - size of index range as a whole
    //      * Local work size - size of work-groups that divide global space. Work items in groups execute concurrently
    size_t global[2] = {width, height};
    size_t local[2] = {16, 16};
    cl(clEnqueueNDRangeKernel(queue, kernel, 2, nullptr, global, local, 0, nullptr, nullptr));

}

void Open_cl_engine::read_image(uint8_t* img, size_t width, size_t height) {
    size_t origin[3] = {0, 0, 0};
    size_t depth[3] = {width, height, 1};
    // Enqueueing image read
    cl(clEnqueueReadImage(queue, cl_img, CL_TRUE,
                          origin, depth, 0, 0, img,
                          0, nullptr, nullptr));
}

void Open_cl_engine::execute_and_wait() {

    // Submitting commands in queue for the execution
    cl(clFlush(queue));

    // Blocking until all prev. enqueued commands in the command queue have completed
    cl(clFinish(queue));
}

void Open_cl_engine::clean_up() {
    cl(clReleaseKernel(kernel));
    cl(clReleaseProgram(program));
    cl(clReleaseMemObject(cl_img));

    cl(clReleaseCommandQueue(queue));
    cl(clReleaseContext(ctx));
}


cl_device_id Open_cl_engine::get_device() {
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

        return devices.at(0);
    }

    return nullptr;
}

void Open_cl_engine::build(std::string source) {
    cl_int err;

    const char* string = source.data();
    const size_t length = source.size();

    program = clCreateProgramWithSource(ctx, 1, &string, &length, &err);
    cl_ok(err);

    const char* options = "";

    err = clBuildProgram(program, 1, &device, options, nullptr, nullptr);

    if (err == CL_BUILD_PROGRAM_FAILURE) {

        size_t value_sz;
        cl(clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &value_sz));

        std::vector<unsigned char> value;
        cl(clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, value_sz, value.data(), nullptr));


        throw std::runtime_error("Failed to build the program: " + to_string(value.data()));
    }
}



