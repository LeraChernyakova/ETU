#include "../include/utils.hpp"
#include <chrono>
#include <iostream>


int main() {
    if (!ocl_init()) throw;
    static const int res_w = 4096, res_h = 4096;
    cl_device_id device = create_device();
    cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    cl_program program = build_program(ctx, device);
    cl_kernel kernel = clCreateKernel(program, "mandelbrot", NULL);
    cl_command_queue queue = clCreateCommandQueue(ctx, device, 0, NULL);
    
    cl_mem buffer = clCreateBuffer(
        ctx,
        CL_MEM_WRITE_ONLY,
        sizeof(cl_uint) * res_w * res_h,
        NULL,
        NULL
    );

    std::vector<cl_uint> pixels(res_w * res_h);
    auto start_programm = std::chrono::high_resolution_clock::now();

    invoke_kernel(
        kernel,
        queue,
        buffer,
        pixels.data(),
        res_w,
        res_h,
        50
    );

    auto end_programm = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_programm - start_programm);
    std::cout << duration.count() << std::endl;

    save_result(pixels.data(), res_w, res_h);

    clReleaseKernel(kernel);
    clReleaseMemObject(buffer);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(ctx);
    return 0;
}