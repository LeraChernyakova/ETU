#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <CL/opencl.hpp>
#include "mandelbrot.h"

using namespace std;

int align(int x, int y) {
    return (x + y - 1) / y * y;
}


void save_ppm(const cl_uint* p, int w, int h, const char* output_name) {
    std::ofstream file(output_name, std::ios::binary);
    file << "P6\n" << w << " " << h << "\n255\n";
    for (int y = 0; y < h; ++y) {
        const cl_uint* line = p + w * y;
        for (int x = 0; x < w; x++) {
            file.write((const char*)(line + x), 3);
        }
    }
}



cl_device_id create_device() {
    cl_platform_id platform;
    cl_device_id dev;
    cl_int err = 0;
    err |= clGetPlatformIDs(1, &platform, NULL);
    err |= clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
    if (err == CL_DEVICE_NOT_FOUND) {
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
    }
    if (err) throw;
    return dev;
}

cl_program build_program(cl_context ctx, cl_device_id dev) {
    int err = 0;

    std::ifstream t("mandelbrot.cl");
    std::string src((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    t.close();

    const char* src_text = src.data();
    size_t src_length = src.size();

    cl_program program = clCreateProgramWithSource(ctx, 1, &src_text, &src_length, &err);

    err |= clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

    if (err) throw;

    return program;
}


void invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem buff,
                   cl_uint* result, float x, float y, float mag, int w, int h, int iters) {
    cl_int err = 0;

    err |= clSetKernelArg(kernel, 0, sizeof(float), &x);
    err |= clSetKernelArg(kernel, 1, sizeof(float), &y);
    err |= clSetKernelArg(kernel, 2, sizeof(float), &mag);
    err |= clSetKernelArg(kernel, 3, sizeof(int), &iters);
    err |= clSetKernelArg(kernel, 4, sizeof(int), &w);
    err |= clSetKernelArg(kernel, 5, sizeof(int), &h);
    err |= clSetKernelArg(kernel, 6, sizeof(buff), &buff);
    err |= clSetKernelArg(kernel, 7, sizeof(int), &w);


    size_t local_size[2] = { 256, 1 };
    size_t global_size[2] = { static_cast<size_t>(align(w, local_size[0])), static_cast<size_t>(align(h, local_size[1])) };

    err |= clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);

    err |= clEnqueueReadBuffer(queue, buff, CL_TRUE, 0, sizeof(int) * w * h, result, 0, NULL, NULL);

    clFinish(queue);
}



int main() {
    const int res_w = 4096, res_h = 4096;
    int max_iters = 1000;
    cl_int err = 0;

    cl_device_id device = create_device();
    cl_context context = clCreateContext(0, 1, &device, NULL, NULL, NULL);

    cl_program program = build_program(context, device);
    cl_kernel kernel = clCreateKernel(program, "mandelbrot", &err);
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);
    cl_mem buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(cl_uint) * res_w * res_h, NULL, NULL);


    std::vector<cl_uint> pixels(res_w * res_h);

    auto start_time = chrono::high_resolution_clock::now();
    invoke_kernel(kernel, queue, buff, pixels.data(), -.5f, 0, 4.5f, res_w, res_h, max_iters);
    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time).count();
    cout<< "GPU time: " << duration << " ms\n";

    save_ppm(pixels.data(), res_w, res_h, "gpu_mandelbrot.ppm");

    clReleaseKernel(kernel);
    clReleaseMemObject(buff);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);


    std::vector<unsigned int> proc_pxls(res_w * res_h);

    start_time = chrono::high_resolution_clock::now();
    mandelbrot(-0.5, 0, 4.5f, max_iters, res_w, res_h, proc_pxls.data(), res_w);
    stop_time = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time).count();
    cout<< "CPU time: " << duration << " ms\n";

    save_ppm(proc_pxls.data(), res_w, res_h, "cpu_mandelbrot.ppm");
}




