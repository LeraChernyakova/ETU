#include "mandelbrot_gpu.h"

std::string get_program_text() {
    std::ifstream file("./mandelbrot.cl"); // читаем код из файла
    std::stringstream string;
    string << file.rdbuf();
    return string.str();
}

cl_program build_program(cl_context ctx, cl_device_id device) {
    std::string kernel_src = get_program_text(); // чтение кода из файла
    const char* src_text = kernel_src.data(); // путь файла
    size_t src_size = kernel_src.size(); // получить размер строки
    cl_program program = clCreateProgramWithSource(ctx, 1, &src_text, &src_size, NULL);// Создает программный объект для контекста
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL); //Создать исполняемый файл программы
    return program;
}

cl_device_id get_device() { // выбор устройство для использования
    cl_device_id device;
    cl_uint platformsCount = 0;
    clGetPlatformIDs(0, nullptr, &platformsCount); // получаем количество устройств
    std::vector<cl_platform_id> platforms(platformsCount);
    clGetPlatformIDs(platformsCount, platforms.data(), nullptr); // получаем платформы
    clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 1, &device, NULL); // получаем устройство
    return device;
}

void invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem buffer, cl_uint* result, int w, int h, float iters) { // создаём kernel 
    clSetKernelArg(kernel, 0, sizeof(float), &iters); // инициализируем аргументы
    clSetKernelArg(kernel, 1, sizeof(cl_int), &w);
    clSetKernelArg(kernel, 2, sizeof(cl_int), &h);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &buffer);
    size_t local_size[2] = { 256, 1 }; // размер work group
    size_t global_size[2] = {  // размер изображения, кратный размеру work group
        align(w, local_size[0]),
        align(h, local_size[1])
    };
    clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);// отдать команду на запуск kernel
    clEnqueueReadBuffer(queue, buffer, CL_TRUE, 0, sizeof(int) * w * h, result, 0, NULL, NULL);// отдать команду на чтение результата
    clFinish(queue); // подождать завершение всех операций
}