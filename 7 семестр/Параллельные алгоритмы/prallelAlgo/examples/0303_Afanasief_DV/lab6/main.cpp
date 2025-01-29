#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "model/Matrix.h"

#include <CL/cl.h>
#include <libclew/ocl_init.h>

#define MATRIX_SIZE 1024
#define LOCAL_SIZE 16 // block size

using namespace std;


unsigned long get_time_diff(chrono::time_point<std::chrono::steady_clock> first, chrono::time_point<std::chrono::steady_clock> second) {
    return chrono::duration_cast<chrono::microseconds>(second - first).count();
}

cl_device_id create_device() {
    cl_platform_id platform;
    clGetPlatformIDs(1, &platform, nullptr);

    cl_device_id dev;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, nullptr);

    return dev;
}


cl_program build_program(cl_context ctx, cl_device_id dev) {
    int err = 0;
    FILE* file = fopen("../matrix.cl", "rb");
    if (file == NULL) {
        perror("Couldn't read the program file");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long sizes = ftell(file);
    rewind(file);
    char* buffer = (char*)malloc(sizes + 1);
    buffer[sizes] = '\0';
    fread(buffer, sizeof(char), sizes, file);
    fclose(file);
    const char* src_text = buffer;
    size_t src_length = sizes;
    cl_program program = clCreateProgramWithSource(ctx, 1, &src_text, &src_length, &err);
    err |= clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    cout << err << endl;

    if (err) {
        cout << "Thrown error " << err << '\n';
        // Determine the size of the log
        size_t log_size;
        clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        // Allocate memory for the log
        char* log = new char[log_size];

        // Get the log
        clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

        // Print the log
        printf("%s\n", log);
        delete[] log;
        throw;
    };

    return program;
}

unsigned long invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem& A, cl_mem& B, cl_mem& buff,
                            cl_int* result, size_t sizeM) {
    cl_int err = 0;
    err |= clSetKernelArg(kernel, 0, sizeof(A), &A);
    err |= clSetKernelArg(kernel, 1, sizeof(B), &B);
    err |= clSetKernelArg(kernel, 2, sizeof(buff), &buff);
    err |= clSetKernelArg(kernel, 3, sizeof(int), &sizeM);

    size_t local_size[2] = { LOCAL_SIZE, LOCAL_SIZE };
    size_t global_size[2] = { sizeM, sizeM };

    auto start = chrono::steady_clock::now();
    err |= clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);
    err |= clEnqueueReadBuffer(queue, buff, CL_TRUE, 0, sizeof(cl_int) * sizeM * sizeM, result, 0, NULL, NULL);

    clFinish(queue);
    return get_time_diff(start, chrono::steady_clock::now());
}



int main() {
    if (MATRIX_SIZE % LOCAL_SIZE) {
        cout << "Global size (MATRIX_SIZE) is not multiple of LOCAL_SIZE\n";
        return -1;
    }
    if (!ocl_init()) {
        throw std::runtime_error("Can't init OpenCL driver!");
    }
    cl_int err = 0;
    cl_device_id device = create_device();
    cl_int errorCode;
    cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &errorCode);
    cl_program program = build_program(context, device);
    cl_int buff_error = 0;
    cl_kernel kernel = clCreateKernel(program, "matrix", &err);
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);

    Matrix left = Matrix::generate(MATRIX_SIZE);
    Matrix right = Matrix::generate(MATRIX_SIZE);

    cl_mem A = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, left.m.data(), &buff_error);
    cl_mem B = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, right.m.data(), &buff_error);
    cl_mem buff = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_int) * MATRIX_SIZE * MATRIX_SIZE, NULL, NULL);
    std::vector<cl_int> result(MATRIX_SIZE * MATRIX_SIZE, 0);

    auto time = invoke_kernel(kernel, queue, A, B, buff, result.data(), MATRIX_SIZE);
    cout << "time: " << time << "\n";

    clReleaseKernel(kernel);
    clReleaseMemObject(A);
    clReleaseMemObject(B);
    clReleaseMemObject(buff);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);

    return 0;
}




