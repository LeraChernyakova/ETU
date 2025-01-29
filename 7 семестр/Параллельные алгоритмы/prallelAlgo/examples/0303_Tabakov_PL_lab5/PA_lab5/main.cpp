#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <CL/cl.h>
#include <libclew/ocl_init.h>
const int SIZE_W_H = 1024;
const int SIZE_WORK_GROUP = 256;


std::string get_program_text() {
    std::ifstream f("./mandelbrot.cl");
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}


cl_program build_program(cl_context ctx, cl_device_id device) {
    std::string kernel_src = get_program_text();
    const char* src_text = kernel_src.data();
    size_t src_size = kernel_src.size();
    cl_program program = clCreateProgramWithSource(
        ctx,
        1,
        &src_text,
        &src_size,
        NULL
    );
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    return program;
}

cl_device_id create_device() {
    cl_platform_id platform;
    cl_device_id device;
    cl_uint platformsCount = 0;
    clGetPlatformIDs(0, nullptr, &platformsCount);
    std::vector<cl_platform_id> platforms(platformsCount);
    clGetPlatformIDs(platformsCount, platforms.data(), nullptr);
    clGetDeviceIDs(platforms[1], CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    return device;
}

int align(int x, int y) {
    return (x + y - 1) / y * y;
}


void invoke_kernel(
    cl_kernel kernel,
    cl_command_queue queue,
    cl_mem buffer,
    cl_uint* result,
    int w,
    int h,
    float iters 
) {
    clSetKernelArg(kernel, 0, sizeof(float), &iters);
    clSetKernelArg(kernel, 1, sizeof(cl_int), &w);
    clSetKernelArg(kernel, 2, sizeof(cl_int), &h);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &buffer);
    size_t local_size[2] = {SIZE_WORK_GROUP, 1};
    size_t global_size[2] = {
        align(w, local_size[0]),
        align(h, local_size[1])
    };
    clEnqueueNDRangeKernel(
        queue,
        kernel,
        2,
        NULL,
        global_size,
        local_size,
        0,
        NULL,
        NULL
    );
    clEnqueueReadBuffer(
        queue,
        buffer,
        CL_TRUE,
        0,
        sizeof(int) * w * h,
        result,
        0,
        NULL,
        NULL
    );
    clFinish(queue);
}


void save_result(const cl_uint* pixels, int w, int h) {
    std::ofstream file("result.ppm", std::ios::binary);
    file << "P6\n" << w << " " << h << "\n255\n";
    for (int y = 0; y < h; y++) {
        const cl_uint* line = pixels + w * y;
        for (int x = 0; x < w; x++) {
            file.write((const char*)(line + x), 3);
        }
    }
}




int main() {
    if (!ocl_init()) throw;
    static const int res_w = SIZE_W_H, res_h = SIZE_W_H;
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
    std::cout << "GPU time: " << duration.count() << std::endl;

    save_result(pixels.data(), res_w, res_h);

    clReleaseKernel(kernel);
    clReleaseMemObject(buffer);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(ctx);
    return 0;
}
