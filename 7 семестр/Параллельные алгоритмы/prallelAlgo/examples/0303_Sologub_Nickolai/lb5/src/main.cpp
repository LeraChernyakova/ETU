#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <CL/cl.h>
#include <chrono>
#include "mandelbrot.h"
std::string get_program_text() {
    std::ifstream f("./mandelbrot.cl"); // читаем код из файла
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str(); // возвращаем
}


cl_program build_program(cl_context ctx, cl_device_id device) {
    std::string kernel_src = get_program_text(); // получить расположение файла cl
    const char* src_text = kernel_src.data(); // получить путь файла
    size_t src_size = kernel_src.size(); // получить размер строки
    cl_program program = clCreateProgramWithSource(  // Создает программный объект для контекста
        ctx,
        1,
        &src_text,
        &src_size,
        NULL
    );
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL); //Создать исполняемый файл программы
    return program;
}

cl_device_id create_device() { // выбор устройство для использования
    cl_platform_id platform;
    cl_device_id device;
    cl_uint platformsCount = 0;
    clGetPlatformIDs(0, nullptr, &platformsCount); // получаем количество устройств
    std::vector<cl_platform_id> platforms(platformsCount);
    clGetPlatformIDs(platformsCount, platforms.data(), nullptr); // получаем платформы
    clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 1, &device, NULL); // получаем устройство
    return device;
}

int align(int x, int y) { // сделать кратным число
    return (x + y - 1) / y * y;
}


void invoke_kernel(  // создаём kernel
    cl_kernel kernel,
    cl_command_queue queue,
    cl_mem buffer,
    cl_uint* result,
    int w,
    int h,
    float iters
) {
    clSetKernelArg(kernel, 0, sizeof(float), &iters); // инициализируем аргументы
    clSetKernelArg(kernel, 1, sizeof(cl_int), &w);
    clSetKernelArg(kernel, 2, sizeof(cl_int), &h);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &buffer);
    size_t local_size[2] = { 256, 1 }; // задаём размер work group
    size_t global_size[2] = {  // размер изображения, кратный размеру work group
        align(w, local_size[0]), 
        align(h, local_size[1])
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
        sizeof(int) * w * h,
        result,
        0,
        NULL,
        NULL
    );
    clFinish(queue); // подождать завершение всех операций
}
void save_result(const cl_uint* pixels, int w, int h, const char* fileName) {
    std::ofstream file(fileName, std::ios::binary);
    file << "P6\n" << w << " " << h << "\n255\n";
    for (int y = 0; y < h; y++) {
        const cl_uint* line = pixels + w * y;
        for (int x = 0; x < w; x++) {
            file.write((const char*)(line + x), 3);
        }
    }
}

int main() {
    static const int res_w = 4096, res_h = 4096; // определяем размер изображения
    int max_iters = 50;
    cl_device_id device = create_device(); // создаём устройство
    cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, NULL); // создаём контекст
    cl_program program = build_program(ctx, device); // вызываем функцию сборки программы
    cl_kernel kernel = clCreateKernel(program, "mandelbrot", NULL); // получаем kernel из программы
    cl_command_queue queue = clCreateCommandQueueWithProperties(ctx, device, 0, NULL); // создаём очередь

    cl_mem buffer = clCreateBuffer(
        ctx,
        CL_MEM_WRITE_ONLY,
        sizeof(cl_uint) * res_w * res_h,
        NULL,
        NULL
    ); // создаём буффер для сохранения результата

    std::vector<cl_uint> pixels(res_w * res_h); // выделить буффер 
    auto startTime = std::chrono::steady_clock::now(); // засечь время начала
    invoke_kernel( // запускаем отрисовку мандельброта
        kernel,
        queue,
        buffer,
        pixels.data(),
        res_w,
        res_h,
        max_iters
    ); 

    std::chrono::duration<double> endTime = std::chrono::steady_clock::now() - startTime; // закончить время подсчёта
    std::cout << "GPU Time: " << endTime.count() << " seconds" << std::endl;

    save_result(pixels.data(), res_w, res_h,"resultGPU.ppm"); // сохранить ppm файл

    clReleaseKernel(kernel); // очистить данные
    clReleaseMemObject(buffer);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(ctx);
    std::vector<cl_uint> pixelsCpu(res_w * res_h); // выделить буффер 
    auto startTimeCpu = std::chrono::steady_clock::now(); // засечь время начала
    drawMandelbrot(max_iters, res_w, res_h, pixelsCpu.data());
    std::chrono::duration<double> endTimeCpu = std::chrono::steady_clock::now() - startTime; // закончить время подсчёта
    std::cout << "CPU Time: " << endTimeCpu.count() << " seconds" << std::endl;
    save_result(pixelsCpu.data(), res_w, res_h, "resultCPU.ppm");
    return 0;
}

