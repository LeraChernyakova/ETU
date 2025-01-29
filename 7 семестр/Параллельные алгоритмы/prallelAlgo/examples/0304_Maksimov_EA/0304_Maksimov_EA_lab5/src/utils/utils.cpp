#include "utils.h"

// ======== ========

template<typename T>
std::string to_string(T value) {
    std::ostringstream ss;
    ss << value;
    return ss.str();
}

void reportError(cl_int err, const std::string &filename, int line) {
    if (CL_SUCCESS == err)
        return;
    // Таблица с кодами ошибок:
    // libs/clew/CL/cl.h:103
    std::string message = "OpenCL error code " + to_string(err) + " encountered at " + filename + ":" + to_string(line);
    throw std::runtime_error(message);
}

#define OCL_SAFE_CALL(expr) reportError(expr, __FILE__, __LINE__)

// ======== ========

std::string getProgramText() {
    std::ifstream f("./mandelbrot/mandelbrot.cl");
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

cl_program buildProgram(cl_context ctx, cl_device_id device) {
    std::string kernel_src = getProgramText();
    const char* src_text = kernel_src.data();
    size_t src_size = kernel_src.size();

    cl_int err;     // Код ошибки

    cl_program program = clCreateProgramWithSource(
        ctx,
        1,
        &src_text,
        &src_size,
        &err
    );

    if (err != CL_SUCCESS) {
        std::cerr << "Error creating program: " << err << std::endl;
        return nullptr;
    }

    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);

    if (err != CL_SUCCESS) {
        // If the build failed, retrieve and print the build log
        size_t logSize;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);

        std::vector<char> buildLog(logSize);
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, buildLog.data(), NULL);

        std::cerr << "Error in kernel:" << std::endl << buildLog.data() << std::endl;

        return nullptr;
    }

    return program;
}

cl_device_id createDevice() {
    if (!ocl_init())
        throw std::runtime_error("Can't init OpenCL driver!");

    cl_uint platformsCount = 0;
    OCL_SAFE_CALL(clGetPlatformIDs(0, nullptr, &platformsCount));

    std::vector<cl_platform_id> platforms(platformsCount);
    OCL_SAFE_CALL(clGetPlatformIDs(platformsCount, platforms.data(), nullptr));

    if(platformsCount == 0) {
        throw std::runtime_error("No platforms found.");
    }

    cl_platform_id platform = platforms[0];

    cl_uint devicesCount = 0;
    OCL_SAFE_CALL(clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, nullptr, &devicesCount));
    std::vector<cl_device_id> devices(devicesCount);
    OCL_SAFE_CALL(clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, devices.data(), &devicesCount));

    if(devicesCount == 0) {
        throw std::runtime_error("No devices found.");
    }

    return devices[0];
}

size_t align(int x, int y) {       // Минимальное число, кратное Y и не меньше X.
    return (x+y-1) / y * y;
}

void invokeKernel(
    cl_kernel kernel, cl_command_queue queue, cl_mem buffer, cl_uint* result,
    int w, int h,
    float iters
) {
    clSetKernelArg(kernel, 0, sizeof(float), &iters);   // Инициализируем аргументы
    clSetKernelArg(kernel, 1, sizeof(cl_int), &w);
    clSetKernelArg(kernel, 2, sizeof(cl_int), &h);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &buffer);
    size_t local_size[2] = { 256, 1 };                                              // Размер work group
    size_t global_size[2] = { align(w, local_size[0]), align(h, local_size[1]) };   // Размер изображения, кратный work group

    // ==== ====

    clEnqueueNDRangeKernel(     // Запустить Kernel
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
    clEnqueueReadBuffer(        // Получить результат в result
        queue,
        buffer,
        CL_TRUE,
        0,
        sizeof(int) * w*h,
        result,                 // Результат здесь
        0,
        NULL,
        NULL
    );

    clFinish(queue);            // Подождать завершения
    
    return;
}
