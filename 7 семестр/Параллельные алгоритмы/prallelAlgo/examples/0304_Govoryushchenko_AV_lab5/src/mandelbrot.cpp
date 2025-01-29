#include <mandelbrot.h>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <fstream>

#include <CL/cl.h>

#define CHECK_OCL(expr) if (expr) throw std::runtime_error{"OpenCL error"};

void mandelbrotCpu(char *buffer, size_t width, size_t height, size_t maxIters) {
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            float x0 = i * (xScale[1] - xScale[0]) / width + xScale[0];
            float y0 = j * (yScale[1] - yScale[0]) / height + yScale[0];
            float x2 = 0.0f, y2 = 0.0f, w = 0.0f;
            size_t iter = 0;
            for (; x2 + y2 <= 4 && iter < maxIters; iter++) {
                    float x = x2 - y2 + x0;
                    float y = w - x2 - y2 + y0;
                    x2 = x * x;
                    y2 = y * y;
                    w = (x + y) * (x + y);
            }

            size_t pixelPos = (j * width + i) * channels;
            buffer[pixelPos + 0] = static_cast<char>(1.0f / std::atan(iter * 1.0f / maxIters) * 255);
            buffer[pixelPos + 1] = static_cast<char>(1.0f / std::atan(iter * 1.0f / maxIters) * 255);
            buffer[pixelPos + 2] = static_cast<char>(std::cos(iter * 1.0f / maxIters) * 255);
        }
    }
}


void mandelbrotOpencl(char *buffer, size_t width, size_t height, size_t maxIters) {
    cl_platform_id platform;
    cl_device_id dev;
    cl_context context;
    cl_kernel kernel;
    cl_command_queue cmdQueue;
    cl_mem workBuffer;
    cl_program prog;
    cl_int ret;

    CHECK_OCL(clGetPlatformIDs(1, &platform, nullptr));
    CHECK_OCL(clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, nullptr));

    cl_context_properties props[] = {CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties>(platform), 0};
    context = clCreateContext(props, 1, &dev, nullptr, nullptr, &ret);
    CHECK_OCL(ret);
    cmdQueue = clCreateCommandQueueWithProperties(context, dev, nullptr, &ret);
    CHECK_OCL(ret);
    workBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, width * height * channels, nullptr, &ret);
    CHECK_OCL(ret);

    std::ifstream file(kernelFile);
    std::stringstream data;
    data << file.rdbuf();
    std::string content{ data.str() };
    const char *rawText = content.c_str();

    prog = clCreateProgramWithSource(context, 1, &rawText, nullptr, &ret);
    CHECK_OCL(ret);
    CHECK_OCL(clBuildProgram(prog, 1, &dev, nullptr, nullptr, nullptr));
    kernel = clCreateKernel(prog, kernelFunc, &ret);
    CHECK_OCL(ret);
    CHECK_OCL(clReleaseProgram(prog));

    CHECK_OCL(clSetKernelArg(kernel, 0, sizeof(workBuffer), &workBuffer));
    CHECK_OCL(clSetKernelArg(kernel, 1, sizeof(int), &maxIters));
    const size_t globalWorkSize[] = {width, height};
    CHECK_OCL(clEnqueueNDRangeKernel( cmdQueue, kernel, 2, nullptr,
        globalWorkSize, workgroupSize, 0, nullptr, nullptr ));
    CHECK_OCL(clEnqueueReadBuffer( cmdQueue, workBuffer, CL_FALSE, 0,
        width * height * channels, buffer, 0, nullptr, nullptr));
    CHECK_OCL(clFinish(cmdQueue));
    CHECK_OCL(clReleaseMemObject(workBuffer));
    CHECK_OCL(clReleaseCommandQueue(cmdQueue));
    CHECK_OCL(clReleaseContext(context));
}