#include "mandelbrot_computer.h"

#include <stdexcept>
#include <fstream>

inline size_t align(size_t x, size_t y) {
    return (x + y - 1) / y * y;
}

MandelbrotComputer::MandelbrotComputer(size_t _height, size_t _width, float _ratio, size_t _iterLimit):
    height(_height),
    width(_width),
    ratio(_ratio),
    iterLimit(_iterLimit),
    pixelsBuffer(width * height)
{
    computeMandelbrot();
}

MandelbrotComputer::~MandelbrotComputer()
{
}

cl_device_id MandelbrotComputer::createDevice()
{
    cl_platform_id platform;
    clGetPlatformIDs(1, &platform, nullptr);

    cl_device_id dev;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, nullptr);

    return dev;
}

cl_program MandelbrotComputer::buildProgramCL(cl_context ctx, cl_device_id device, const std::string &clFilename)
{
    std::ifstream stream(clFilename);
    std::string code;
    std::getline(stream, code, '\0');
    const char *codePtr = code.c_str();
    size_t codeSize = code.size();
    cl_program program = clCreateProgramWithSource(ctx, 1, &codePtr, &codeSize, &error);
    error = clBuildProgram(program, 0, nullptr, nullptr, nullptr, nullptr);
    return program;
}

void MandelbrotComputer::execute(cl_kernel kernel, cl_command_queue queue, cl_mem buffer,
             cl_uint *resultPointer, float ratio, cl_int width, cl_int height,
             cl_int iterLimit)
{

    clSetKernelArg(kernel, 0, sizeof(cl_int), &height);
    clSetKernelArg(kernel, 1, sizeof(cl_int), &width);
    clSetKernelArg(kernel, 2, sizeof(float), &ratio);
    clSetKernelArg(kernel, 3, sizeof(cl_int), &iterLimit);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), &buffer);

    std::vector<size_t> local_size = {256, 1};
    std::vector<size_t> global_size = {align(width, local_size[0]), align(height, local_size[1])};

    clEnqueueNDRangeKernel(
        queue,
        kernel,
        2,
        nullptr,
        global_size.data(),
        local_size.data(),
        0,
        nullptr,
        nullptr);

    const size_t bufferSize = sizeof(cl_uint) * width * height;

    clEnqueueReadBuffer(
        queue,
        buffer,
        CL_TRUE,
        0,
        bufferSize,
        resultPointer,
        0,
        nullptr,
        nullptr);

    clFinish(queue);
}

void MandelbrotComputer::computeMandelbrot()
{
    if (!ocl_init()) error = -1;

    const auto clFilename = "/home/igor/Code/c++Tasks/lb5/src/mandelbrot.cl";
    const auto kernelName = "computeMandelbrot";

    cl_device_id device = createDevice();
    cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &error);

    cl_program program = buildProgramCL(context, device, clFilename);

    cl_kernel kernel = clCreateKernel(program, kernelName, &error);

    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &error);

    const size_t bufferSize = sizeof(cl_uint) * width * height;
    cl_mem buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bufferSize, nullptr, &error);

    execute(kernel, queue, buffer, pixelsBuffer.data(), ratio, width, height, iterLimit);

    clReleaseKernel(kernel);
    clReleaseMemObject(buffer);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);
}
