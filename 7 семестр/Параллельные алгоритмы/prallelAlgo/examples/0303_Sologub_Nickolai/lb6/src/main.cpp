#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <CL/cl.h>
#include <chrono>
#include "matrix.h"
#define LOCAL_SIZE 4 // block size
std::string get_program_text() {
    std::ifstream f("./matrixMult.cl"); // читаем код из файла
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str(); // возвращаем
}


cl_program build_program(cl_context ctx, cl_device_id device) {
    int err = 0;

    std::ifstream t("matrixMult.cl");
    std::string src((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    t.close();
    src = "#define BS " + std::to_string(LOCAL_SIZE) + "\n\n" + src;
    const char* src_text = src.data();
    size_t src_length = src.size();

    cl_program program = clCreateProgramWithSource(ctx, 1, &src_text, &src_length, &err);
    err |= clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

    if (err) {
        std::cout << "Thrown error " << err << '\n';
        // Determine the size of the log
        size_t log_size;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        // Allocate memory for the log
        char* log = new char[log_size];

        // Get the log
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

        // Print the log
        printf("%s\n", log);
        delete[] log;
        throw;
    };

    return program;
}

cl_device_id create_device() { // выбор устройство для использования
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




void invoke_kernel(  // создаём kernel
    cl_kernel kernel,
    cl_command_queue queue,
    cl_mem& A, 
    cl_mem& B, 
    cl_mem& buffer,
    cl_int* result, 
    const int size
) {
    clSetKernelArg(kernel, 0, sizeof(A), &A); // инициализируем аргументы
    clSetKernelArg(kernel, 1, sizeof(B), &B);
    clSetKernelArg(kernel, 2, sizeof(buffer), &buffer);
    clSetKernelArg(kernel, 3, sizeof(int), &size);
    size_t local_size[2] = { LOCAL_SIZE, LOCAL_SIZE }; // задаём размер work group
    size_t global_size[2] = { 
        size, 
        size
    };
    clEnqueueNDRangeKernel( // отдать команду на запуск kernel
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
    clEnqueueReadBuffer( // отдать команду на чтение результата
        queue,
        buffer,
        CL_TRUE,
        0,
        sizeof(cl_int) * size * size,
        result,
        0,
        NULL,
        NULL
    );
    clFinish(queue); // подождать завершение всех операций
}


int main() {
    cl_int err = 0;
    cl_device_id device = create_device(); // создаём устройство
    cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, &err); // создаём контекст
    if (err) std::cout << "Error while creating context\n";
    cl_program program = build_program(ctx, device); // вызываем функцию сборки программы
    cl_kernel kernel = clCreateKernel(program, "mult", &err); // получаем kernel из программы
    if (err) std::cout << "Error while creating kernel\n";
    cl_command_queue queue = clCreateCommandQueueWithProperties(ctx, device, 0, &err); // создаём очередь
    if (err) std::cout << "Error while creating queue\n";
    int matrixSize = 32;
    cl_int buff_error = 0;
    Matrix First(matrixSize, matrixSize);
    Matrix Second(matrixSize, matrixSize);
   // std::cout << "Первая" << std::endl;
   // std::cout << First << std::endl;
   // std::cout << "--------" << std::endl;
   // std::cout << "Вторая" << std::endl;
    //std::cout << Second << std::endl;
   // std::cout << "--------" << std::endl;
    cl_mem A = clCreateBuffer(ctx, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * matrixSize * matrixSize, First.matrix.data(), &buff_error);
    if (buff_error) std::cout << "Error while creating buffer A\n";
    cl_mem B = clCreateBuffer(ctx, CL_MEM_USE_HOST_PTR, sizeof(cl_int) * matrixSize * matrixSize, Second.matrix.data(), &buff_error);
    if (buff_error) std::cout << "Error while creating buffer B\n";
    cl_mem buff = clCreateBuffer(ctx, CL_MEM_READ_WRITE, sizeof(cl_int) * matrixSize * matrixSize, NULL, &buff_error);
    if (buff_error) std::cout << "Error while creating result buffer\n";
    std::vector<cl_int> result(matrixSize * matrixSize, 0);// выделить буффер  
    auto startTime = std::chrono::steady_clock::now(); // засечь время начала
    invoke_kernel( // запускаем отрисовку мандельброта
        kernel,
        queue,
        A,
        B,
        buff,
        result.data(),
        matrixSize
    );
    Matrix res(matrixSize, matrixSize);
    res.matrix = result;
    std::cout << "Result: " << res.compare(First*Second) << std::endl;

    std::chrono::duration<double> endTime = std::chrono::steady_clock::now() - startTime; // закончить время подсчёта
    std::cout << "GPU Time: " << endTime.count() << " seconds" << std::endl;

    clReleaseKernel(kernel); // очистить данные
    clReleaseMemObject(A);
    clReleaseMemObject(B);
    clReleaseMemObject(buff);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(ctx);
    return 0;
}

