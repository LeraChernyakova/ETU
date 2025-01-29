//
// Created by dima on 18.11.23.
//
#include "mandelbrot.h"

#define OCL_SAFE_CALL(expr) report_error(expr, __FILE__, __LINE__)

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


size_t align(size_t x, size_t y) {
    return (x + y - 1) / y * y;
}

void execute(cl_kernel kernel, cl_command_queue queue, cl_mem buffer,
        cl_uint* resultPointer, float ratio, cl_int width, cl_int height,
        cl_int iterLimit) {

    OCL_SAFE_CALL(clSetKernelArg(kernel, 0, sizeof(cl_int), &height));
    OCL_SAFE_CALL(clSetKernelArg(kernel, 1, sizeof(cl_int), &width));
    OCL_SAFE_CALL(clSetKernelArg(kernel, 2, sizeof(float), &ratio));
    OCL_SAFE_CALL(clSetKernelArg(kernel, 3, sizeof(cl_int), &iterLimit));
    OCL_SAFE_CALL(clSetKernelArg(kernel, 4, sizeof(cl_mem), &buffer));

    std::vector<size_t> local_size = {256, 1};
    std::vector<size_t> global_size = {align(width, local_size[0]), align(height, local_size[1])};

    OCL_SAFE_CALL(
            clEnqueueNDRangeKernel(
                    queue,
                    kernel,
                    2,
                    nullptr,
                    global_size.data(),
                    local_size.data(),
                    0,
                    nullptr,
                    nullptr
            )
    );

    const size_t bufferSize = sizeof(cl_uint) * width * height;
    OCL_SAFE_CALL(
            clEnqueueReadBuffer(
                    queue,
                    buffer,
                    CL_TRUE,
                    0,
                    bufferSize,
                    resultPointer,
                    0,
                    nullptr,
                    nullptr
            )
    );

    clFinish(queue);
}

cl_device_id createDevice() {
    cl_platform_id platform;
    OCL_SAFE_CALL(clGetPlatformIDs(1, &platform, nullptr));

    cl_device_id dev;
    OCL_SAFE_CALL(clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, nullptr));

    return dev;
}

cl_program buildProgramCL(cl_context ctx, cl_device_id device, const std::string& clFilename) {
    int errorCode;
    std::ifstream stream(clFilename);
    std::string code = to_string(stream.rdbuf());
    const char* codePointer = code.c_str();
    size_t codeSize = code.size();
    cl_program program = clCreateProgramWithSource(ctx, 1, &codePointer, &codeSize, &errorCode);
    OCL_SAFE_CALL(errorCode);
    errorCode = clBuildProgram(program, 0, nullptr, nullptr, nullptr, nullptr);
    OCL_SAFE_CALL(errorCode);
    return program;
}


std::vector<unsigned int> computeMandelbrot(int height, int width, float ratio, int iterLimit){
    if (!ocl_init()) {
        throw std::runtime_error("Can't init OpenCL driver!");
    }

    const auto clFilename = "../mandelbrot.cl";
    const auto kernelName = "computeMandelbrot";

    cl_int errorCode;
    cl_device_id device = createDevice();
    cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &errorCode);

    cl_program program = buildProgramCL(context, device, clFilename);

    cl_kernel kernel = clCreateKernel(program, kernelName, &errorCode);
    OCL_SAFE_CALL(errorCode);

    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &errorCode);
    OCL_SAFE_CALL(errorCode);

    const size_t bufferSize = sizeof(cl_uint) * width * height;
    cl_mem buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bufferSize, nullptr, &errorCode);
    OCL_SAFE_CALL(errorCode);

    std::vector<unsigned int> pixelsBuffer(width * height);
    execute(kernel, queue, buffer, pixelsBuffer.data(), ratio, width, height, iterLimit);

    clReleaseKernel(kernel);
    clReleaseMemObject(buffer);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);

    return pixelsBuffer;
}
