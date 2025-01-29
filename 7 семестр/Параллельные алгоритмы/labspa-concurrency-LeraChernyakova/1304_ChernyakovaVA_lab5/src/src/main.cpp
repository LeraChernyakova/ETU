#include "../include/utils.hpp"
#include <chrono>
#include <iostream>
#include "matrix.h"

int main() {
    if (!ocl_init()) throw;
    static const int size = 1024;
    cl_device_id device = create_device();
    cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    cl_program program = build_program(ctx, device);
    cl_kernel kernel = clCreateKernel(program, "multiply", NULL);
    cl_command_queue queue = clCreateCommandQueue(ctx, device, 0, NULL);

    std::pair<std::vector<int>, std::vector<int>> task = generate_task(size);
    std::vector<int> left_matrix = task.first;
    std::vector<int> right_matrix = task.second;

    std::vector<int> result(size * size);
    
    cl_mem left = clCreateBuffer(ctx, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * size * size, left_matrix.data(), NULL);

    cl_mem right = clCreateBuffer(ctx, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * size * size, right_matrix.data(), NULL);

    cl_mem result_buffer = clCreateBuffer(ctx, CL_MEM_READ_WRITE, sizeof(cl_int) * size * size, NULL, NULL);

    auto start_programm = std::chrono::high_resolution_clock::now();
    
    invoke_kernel(kernel, queue, left, right,result_buffer,result.data(), size);

    auto end_programm = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end_programm - start_programm).count();
    std::cout << duration << std::endl;

    save_result(result.data(), size, "GPU.txt");

    Matrix m1 (size, size, left_matrix);
    Matrix m2 (size, size, right_matrix);

    save_result(parallelBlocks(m1, m2, 7)._matrix.data(), size, "CPU.txt");

    clReleaseKernel(kernel);
    clReleaseMemObject(left);
    clReleaseMemObject(right);
    clReleaseMemObject(result_buffer);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(ctx);
    return 0;
}