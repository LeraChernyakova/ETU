#include <matrixOCL.h>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>

#include <CL/cl.h>

#define CHECK_OCL(expr) if (expr) throw std::runtime_error{"OpenCL error"};



Matrix multiplyMatricesOcl(const Matrix& lm, const Matrix& rm) {
    cl_platform_id platform;
    cl_device_id dev;
    cl_context context;
    cl_kernel kernel;
    cl_command_queue cmdQueue;
    cl_mem rmBuffer, lmBuffer, resBuffer;
    cl_program prog;
    cl_int ret;

    Matrix resMatrix(lm.getRows(), rm.getCols());

    CHECK_OCL(clGetPlatformIDs(1, &platform, nullptr));
    CHECK_OCL(clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, nullptr));

    cl_context_properties props[] = {CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties>(platform), 0};
    context = clCreateContext(props, 1, &dev, nullptr, nullptr, &ret);
    CHECK_OCL(ret);
    cmdQueue = clCreateCommandQueueWithProperties(context, dev, nullptr, &ret);
    CHECK_OCL(ret);
    lmBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, lm.getRows() * lm.getCols() * sizeof(int), (void*)lm.data(), &ret);
    CHECK_OCL(ret);
    rmBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, rm.getRows() * rm.getCols() * sizeof(int), (void*)rm.data(), &ret);
    CHECK_OCL(ret);
    resBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, lm.getRows() * rm.getCols() * sizeof(int), nullptr, &ret);
    CHECK_OCL(ret);

    std::ifstream file(kernelFile);
    std::stringstream data;
    data << file.rdbuf();
    std::string content{data.str()};
    const char *rawText = content.c_str();

    prog = clCreateProgramWithSource(context, 1, &rawText, nullptr, &ret);
    CHECK_OCL(ret);
    CHECK_OCL(clBuildProgram(prog, 1, &dev, nullptr, nullptr, nullptr));
    kernel = clCreateKernel(prog, kernelFunc, &ret);
    CHECK_OCL(ret);
    CHECK_OCL(clReleaseProgram(prog));

    CHECK_OCL(clSetKernelArg(kernel, 0, sizeof(lmBuffer), &lmBuffer));
    CHECK_OCL(clSetKernelArg(kernel, 1, sizeof(rmBuffer), &rmBuffer));
    CHECK_OCL(clSetKernelArg(kernel, 2, sizeof(resBuffer), &resBuffer));
    const size_t globalWorkSize[] = {static_cast<size_t>(resMatrix.getRows()),
        static_cast<size_t>(resMatrix.getCols())};
    CHECK_OCL(clEnqueueNDRangeKernel(cmdQueue, kernel, 2, nullptr,
        globalWorkSize, workgroupSize, 0, nullptr, nullptr));
    CHECK_OCL(clEnqueueReadBuffer(cmdQueue, resBuffer, CL_FALSE, 0,
        resMatrix.getRows() * resMatrix.getCols() * sizeof(int), resMatrix.data(), 0, nullptr, nullptr));

    CHECK_OCL(clFinish(cmdQueue));
    CHECK_OCL(clReleaseMemObject(lmBuffer));
    CHECK_OCL(clReleaseMemObject(rmBuffer));
    CHECK_OCL(clReleaseMemObject(resBuffer));
    CHECK_OCL(clReleaseCommandQueue(cmdQueue));
    CHECK_OCL(clReleaseContext(context));

    return resMatrix;
}