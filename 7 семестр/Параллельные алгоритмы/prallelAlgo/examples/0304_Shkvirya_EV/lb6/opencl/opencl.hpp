#pragma once
#include <CL/cl.h>
#include <vector>
#include <stdexcept>
#include "assert_cl.h"

using namespace std;

class OpenCl {
private:
    cl_device_id device;
    cl_context context;
    cl_command_queue commandQueue;
    cl_kernel kernel;
    cl_program program;
    cl_mem clImage;

    cl_mem firstBuffer = nullptr;
    cl_mem secondBuffer = nullptr;
    cl_mem resultBuffer = nullptr;

public:
    void init() {
        cl_int errorCode;

        // Получаем девайс (придёт либо CPU, либо GPU)
        device = createDevice();

        // Создаём контекс (объект, отвечающий за конкретную сессию взаимодействия с устройством)
        context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &errorCode);
        cl_ok(errorCode);

        // Создаём очередь для исполнения команд
        commandQueue = clCreateCommandQueueWithProperties(context, device, nullptr, &errorCode);
        cl_ok(errorCode);
    }

    void loadProgram(string sourceClCode, string kernelName) {
        cl_int errorCode;

        // Собираем программу по исходному CL-коду
        buildProgram(move(sourceClCode));

        // Создаём ядро с уже скомпилированной программой
        kernel = clCreateKernel(program, kernelName.data(), &errorCode);
        cl_ok(errorCode);
    }

    void createImage(int width, int height, int squareSize) {
        cl_int errorCode;

        // Параметры изображения
        cl_image_format format;
        format.image_channel_order = CL_RGBA;
        format.image_channel_data_type = CL_UNSIGNED_INT8;

        cl_image_desc description;
        description.image_type = CL_MEM_OBJECT_IMAGE2D;
        description.image_width = width;
        description.image_height = height;
        description.image_depth = 0;
        description.image_array_size = 0;
        description.image_row_pitch = 0;
        description.image_slice_pitch = 0;
        description.num_mip_levels = 0;
        description.num_samples = 0;
        description.buffer = nullptr;

        // Создаём изображение с определёнными параметрами
        clImage = clCreateImage(context, CL_MEM_WRITE_ONLY, &format, &description, nullptr, &errorCode);
        cl_ok(errorCode);

        // Устанавливаем изображение как аргумент функции в .cl
        cl(clSetKernelArg(kernel, 0, sizeof(clImage), &clImage));

        size_t global[2] = {(size_t)width, (size_t)height}; // задаём глобальный размер изображения
        size_t local[2] = {(size_t)squareSize, (size_t)squareSize}; // задаём локальный размер обрабатуемого блока изображения
        cl(clEnqueueNDRangeKernel(commandQueue, kernel, 2, nullptr, global, local, 0, nullptr, nullptr));
    }

    void readImage(uint8_t* image, int width, int height) {
        size_t origin[3] = {0, 0, 0};
        size_t depth[3] = {(size_t)width, (size_t)height, 1};
        clEnqueueReadImage(commandQueue, clImage, CL_TRUE, origin, depth, 0, 0, image, 0, nullptr, nullptr);
    }

    void createBuffers(int matricesSize, vector<int> &firstBufferData, vector<int> &secondBufferData, int workGroupSize) {
        cl_int errorCode;

        firstBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * matricesSize * matricesSize, firstBufferData.data(), &errorCode);
        cl_ok(errorCode);
        secondBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int) * matricesSize * matricesSize, secondBufferData.data(), &errorCode);
        cl_ok(errorCode);
        resultBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * matricesSize * matricesSize, nullptr, &errorCode);
        cl_ok(errorCode);

        // Добавляем аргументы к ядру, чтобы потом их достать
        cl(clSetKernelArg(kernel, 0, sizeof(cl_mem), &resultBuffer));
        cl(clSetKernelArg(kernel, 1, sizeof(cl_mem), &firstBuffer));
        cl(clSetKernelArg(kernel, 2, sizeof(cl_mem), &secondBuffer));
        cl(clSetKernelArg(kernel, 3, sizeof(int), &matricesSize));

        size_t global[2] = {(size_t)matricesSize, (size_t)matricesSize};  // задаём глобальный размер матрицы (вся задача)
        size_t local[2] = {(size_t)workGroupSize, (size_t)workGroupSize}; // задаём локальный размер обрабатуемого блока матрицы (рабочая группа)
        cl(clEnqueueNDRangeKernel(commandQueue, kernel, 2, nullptr, global, local, 0, nullptr, nullptr));
    }

    void readBuffer(int *result, int bufferSize) {
        // Добавляем задачу на чтение буфера
        cl(clEnqueueReadBuffer(commandQueue, resultBuffer, CL_TRUE,
                               0, sizeof(int) * bufferSize, result,
                               0, nullptr, nullptr));
    }

    void startAndWait() {
        // запускаем...
        clFlush(commandQueue);
        // ...и блокируем текущий поток до выполнения всех команд
        clFinish(commandQueue);
    }

    void destroy() {
        clReleaseKernel(kernel);
        clReleaseProgram(program);
        clReleaseMemObject(clImage);
        clReleaseCommandQueue(commandQueue);
        clReleaseContext(context);
    }
private:
    static cl_device_id createDevice() {
        // получаем количество платформ
        cl_uint platformAmount = 0;
        cl(clGetPlatformIDs(0, nullptr, &platformAmount));

        // получаем доступные платформы
        vector<cl_platform_id> platforms(platformAmount);
        clGetPlatformIDs(platformAmount, platforms.data(), nullptr);

        for (const auto & platformId : platforms) {
            // получаем количество девайсов
            cl_uint deviceAmount = 0;
            cl(clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 0, nullptr, &deviceAmount));
            if (deviceAmount == 0) {
                continue;
            }

            // получаем доступные устройства
            vector<cl_device_id> devices(deviceAmount);
            cl(clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 1, devices.data(), nullptr));

            return devices.at(0);
        }

        return nullptr;
    }

    void buildProgram(const string& sourceClCode) {
        const char* sourceCode = sourceClCode.data();
        const size_t sourceCodeLength = sourceClCode.size();

        cl_int errorCode;
        // создаём программу по исходному коду
        program = clCreateProgramWithSource(context, 1, &sourceCode, &sourceCodeLength, &errorCode);
        cl_ok(errorCode);

        const char* options = "";
        // собираем программу
        errorCode = clBuildProgram(program, 1, &device, options, nullptr, nullptr);
        if (errorCode == CL_BUILD_PROGRAM_FAILURE) {
            throw runtime_error("Failed to build the program");
        }
    }
};