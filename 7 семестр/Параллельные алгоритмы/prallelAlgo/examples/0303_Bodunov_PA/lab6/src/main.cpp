#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <iostream>
#include <vector>
#include <chrono>
#include <CL/opencl.hpp>
#include "Matrix.h"

#define LOCAL_SIZE 16
#define MATRIX_SIZE 4096

using namespace std;


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

    std::ifstream t("matrix.cl");
    std::string src((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    t.close();

    const char* src_text = src.data();
    size_t src_length = src.size();

    cl_program program = clCreateProgramWithSource(ctx, 1, &src_text, &src_length, &err);

    err |= clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

    if (err) throw;

    return program;
}


void invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem& A, cl_mem& B, cl_mem& buff, cl_int* result, const size_t size) {
    clSetKernelArg(kernel, 0, sizeof(A), &A);
    clSetKernelArg(kernel, 1, sizeof(B), &B);
    clSetKernelArg(kernel, 2, sizeof(buff), &buff);
    clSetKernelArg(kernel, 3, sizeof(int), &size);


    size_t local_size[2] = { LOCAL_SIZE, LOCAL_SIZE };
    size_t global_size[2] = { size, size };
    clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);
    clEnqueueReadBuffer(queue, buff, CL_TRUE, 0, sizeof(cl_int) * size * size, result, 0, NULL, NULL);

    clFinish(queue);
}


int main()
{
    Matrix matrix1(MATRIX_SIZE, MATRIX_SIZE, true);
    Matrix matrix2(MATRIX_SIZE, MATRIX_SIZE, true);
    Matrix matrix_res(MATRIX_SIZE, MATRIX_SIZE, true);

    std::vector<cl_int> gpu_res(MATRIX_SIZE * MATRIX_SIZE, 0);

    cl_device_id device = create_device();
    cl_context context = clCreateContext(0, 1, &device, NULL, NULL, NULL);
    cl_program program = build_program(context, device);
    cl_kernel kernel = clCreateKernel(program, "mult_matrix", NULL);
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, 0, NULL);


    cl_mem A = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, matrix1.matrix.data(), NULL);
    cl_mem B = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, matrix2.matrix.data(), NULL);
    cl_mem buff = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, NULL, NULL);


    auto start_time = chrono::high_resolution_clock::now();
    invoke_kernel(kernel, queue, A, B, buff, gpu_res.data(), MATRIX_SIZE);
    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time).count();
    cout<< "GPU Matrix multiply time: " << duration << " ms\n";

//    matrix_res = matrix1 * matrix2;

//    for (int i = 0; i < matrix_res.rows; i++){
//        for (int j = 0; j < matrix_res.cols; j++){
//            cout << gpu_res[i * matrix_res.cols + j] << " ";
//        }
//        cout << endl;
//    }
//    cout << "\n\n------------------------------------------\n\n";

//    cout << matrix_res;

//    if (matrix_res == gpu_res)
//        cout << "Matrix are equal\n";
//    else
//        cout << "Matrix aren't equal\n";


    clReleaseKernel(kernel);
    clReleaseMemObject(A);
    clReleaseMemObject(B);
    clReleaseMemObject(buff);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);
}
