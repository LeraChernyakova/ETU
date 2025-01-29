#include "matrix_cl.h"

#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <assert.h>

inline size_t align(size_t x, size_t y)
{
    return (x + y - 1) / y * y;
}


void matrixToVector(Matrix &matrix, std::vector<unsigned> &res)
{
    size_t offset{0};
    for (auto &vec : matrix)
    {
        std::copy(vec.begin(), vec.end(), res.begin() + offset);
        offset += vec.size();
    }
}

MatrixCl::MatrixCl(Matrix &m1_, Matrix &m2_, size_t workGroupSize_) : workGroupSize(workGroupSize_),
                                                                      sideSize(m1_.size()),
                                                                      matrix1(m1_.size() * m1_.size()),
                                                                      matrix2(m1_.size() * m1_.size()),
                                                                      result(m1_.size() * m1_.size())
{
    matrixToVector(m1_, matrix1);
    matrixToVector(m2_, matrix2);
}

MatrixCl::~MatrixCl()
{
}

cl_device_id MatrixCl::createDevice()
{
    cl_platform_id platform;
    clGetPlatformIDs(1, &platform, nullptr);

    cl_device_id dev;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, nullptr);

    return dev;
}

cl_program MatrixCl::buildProgramCL(cl_context ctx, cl_device_id device, const std::string &clFilename)
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

void MatrixCl::execute( cl_kernel kernel,
                        cl_command_queue queue,
                        cl_context context)
{
    const size_t bufferSize = sizeof(unsigned) * result.size();
    cl_mem m1Buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, bufferSize, nullptr, &error);
    cl_mem m2Buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, bufferSize, nullptr, &error);
    cl_mem resBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, bufferSize, nullptr, &error);

    error = clEnqueueWriteBuffer(queue, m1Buffer, CL_TRUE, 0, sizeof(unsigned) * matrix1.size(), matrix1.data(), 0, NULL, NULL);
    
    error = clEnqueueWriteBuffer(queue, m2Buffer, CL_TRUE, 0, sizeof(unsigned) * matrix2.size(), matrix2.data(), 0, NULL, NULL);
    
    error = clEnqueueWriteBuffer(queue, resBuffer, CL_TRUE, 0, sizeof(unsigned) * result.size(), result.data(), 0, NULL, NULL);
    
    const uint N = sideSize;
    error = clSetKernelArg(kernel, 0, sizeof(uint), &sideSize);
    
    error = clSetKernelArg(kernel, 1, sizeof(cl_mem), &m1Buffer);
    
    error = clSetKernelArg(kernel, 2, sizeof(cl_mem), &m2Buffer);
    
    error = clSetKernelArg(kernel, 3, sizeof(cl_mem), &resBuffer);
    

    std::vector<size_t> local_size = {32, 32};
    std::vector<size_t> global_size = {sideSize, sideSize};

    error = clEnqueueNDRangeKernel(
        queue,
        kernel,
        2,
        nullptr,
        global_size.data(),
        local_size.data(),
        0,
        nullptr,
        nullptr);

    clFinish(queue);

    
    error = clEnqueueReadBuffer(
        queue,
        resBuffer,
        CL_TRUE,
        0,
        bufferSize,
        result.data(),
        0,
        nullptr,
        nullptr);
    
    clReleaseMemObject(m1Buffer);
    clReleaseMemObject(m2Buffer);
    clReleaseMemObject(resBuffer);
}

std::vector<unsigned> &MatrixCl::getResut()
{
    if (!ocl_init())
        error = -1;

    const auto clFilename = "/home/igor/Code/c++Tasks/lb6/src/matrix.cl";
    const auto kernelName = "matrixMult";

    cl_device_id device = createDevice();
    cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &error);

    cl_program program = buildProgramCL(context, device, clFilename);

    cl_kernel kernel = clCreateKernel(program, kernelName, &error);

    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &error);
    
    execute(kernel, queue, context);

    clReleaseKernel(kernel);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);

    return result;
}
