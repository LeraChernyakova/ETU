#include <CL/cl.h>
#include <libclew/ocl_init.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <chrono>

const int BLOCK_SIZE = 16;

using namespace std;
using namespace chrono;

void reportError(cl_int err, const std::string &filename, int line) {
    if (CL_SUCCESS == err)
        return;

    std::string message = "OpenCL error code " + to_string(err) + " encountered at " + filename + ":" + to_string(line);
    throw std::runtime_error(message);
}

#define OCL_SAFE_CALL(expr) reportError(expr, __FILE__, __LINE__)

#ifndef KERNEL_FILE_PATH
#define KERNEL_FILE_PATH "m_mult.cl"
#endif

int main() {
    if (!ocl_init())
        throw std::runtime_error("Can't init OpenCL driver!");

    cl_uint platformsCount = 0;
    OCL_SAFE_CALL(clGetPlatformIDs(0, nullptr, &platformsCount));
    std::cout << "Number of OpenCL platforms: " << platformsCount << std::endl;

    std::vector<cl_platform_id> platforms(platformsCount);
    OCL_SAFE_CALL(clGetPlatformIDs(platformsCount, platforms.data(), nullptr));

    cl_device_id selected_device = nullptr;

    for (int platformIndex = 0; platformIndex < platformsCount; ++platformIndex) {
        std::cout << "Platform " << (platformIndex + 1) << "/" << platformsCount << std::endl;
        cl_platform_id platform = platforms[platformIndex];

        size_t platformNameSize = 0;
        OCL_SAFE_CALL(clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0, nullptr, &platformNameSize));// TODO 1.1

        std::vector<unsigned char> platformName(platformNameSize, 0);

        OCL_SAFE_CALL(clGetPlatformInfo(platform, CL_PLATFORM_NAME, platformNameSize, platformName.data(), &platformNameSize));
        std::cout << "    Platform name: " << platformName.data() << std::endl;

        size_t platformVendorSize = 0;
        OCL_SAFE_CALL(clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, 0, nullptr, &platformVendorSize));

        std::vector<unsigned char> platformVendor(platformVendorSize, 0);

        OCL_SAFE_CALL(clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, platformVendorSize, platformVendor.data(), &platformVendorSize));
        std::cout << "    Platform vendor: " << platformVendor.data() << std::endl;

        cl_uint devicesCount = 0;
        cl_uint num_entries = 0;
        OCL_SAFE_CALL(clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, nullptr, &devicesCount));
        std::cout << "      Number of OpenCL dev-s: " << devicesCount << std::endl;
        std::vector<cl_device_id> devices (devicesCount);
        OCL_SAFE_CALL(clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, devices.data(), &devicesCount));

        for (int deviceIndex = 0; deviceIndex < devicesCount; ++deviceIndex) {
            std::cout << "    >> DEVICE #" << (deviceIndex + 1) << "/" << devicesCount << std::endl;

            cl_device_id device = devices[deviceIndex];

            size_t param_size = 0;
            OCL_SAFE_CALL(clGetDeviceInfo(device, CL_DEVICE_NAME, param_size, nullptr, &param_size));

            std::vector<unsigned char> dev_name (param_size, 0);
            OCL_SAFE_CALL(clGetDeviceInfo(device, CL_DEVICE_NAME, param_size, dev_name.data(), &param_size));
            std::cout << "    Device name: " << dev_name.data() << std::endl;

            cl_device_type dev_type;
            OCL_SAFE_CALL(clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(cl_device_type), &dev_type, &param_size));
            switch (dev_type)
            {
                case CL_DEVICE_TYPE_CPU:
                    std::cout << "    Dev type :: CPU " << std::endl;
                    break;
                case CL_DEVICE_TYPE_GPU:
                    std::cout << "    Dev type :: GPU " << std::endl;
                    break;
                default:
                    std::cout << "    Dev type :: unknown " << std::endl;
                    break;
            }

            cl_ulong glob_mem_size; //bytes
            OCL_SAFE_CALL(clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &glob_mem_size, &param_size));
            std::cout << "   Global memory: " << glob_mem_size/(1024*1024) << "Mb" << std::endl;

            cl_ulong local_mem_size; //bytes
            OCL_SAFE_CALL(clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &local_mem_size, &param_size));
            std::cout << "   Local memory: " << local_mem_size/(1024) << "K" << std::endl;

            selected_device = device;
            break;
        }
    }


    if (!selected_device) {
        cout << "Cannot find appropriate device!";
        return 0;
    }
    cout << "Selected device: " << selected_device << endl;


    cl_int err;
    cl_context context = clCreateContext(NULL, 1, &selected_device, NULL, NULL, &err);
    OCL_SAFE_CALL(err);

    cl_command_queue queue = clCreateCommandQueue(context, selected_device, 0, &err);
    OCL_SAFE_CALL(err);
    cout << "queue and context has been created" << endl;

    int m;
    cout << "Enter matrix size m: ";
    cin >> m;

    float *A = (float*)malloc(sizeof(float) * m * m);
    float *B = (float*)malloc(sizeof(float) * m * m);

    // Populate A and B with random values
    for (int i = 0; i < m * m; ++i) {
        A[i] = rand() / (float)RAND_MAX;
    }

    for (int i = 0; i < m * m; ++i) {
        B[i] = rand() / (float)RAND_MAX;
    }


    // Load kernel source
    const char *filename = KERNEL_FILE_PATH;
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    size_t source_size = ftell(file);
    rewind(file);

    char *source_str = (char*)malloc(source_size + 1);
    source_str[source_size] = '\0';
    fread(source_str, sizeof(char), source_size, file);
    fclose(file);

    // Create and build program
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &err);
    OCL_SAFE_CALL(err);

    err = clBuildProgram(program, 1, &selected_device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        // Determine the reason for the error
        char build_log[16384];
        clGetProgramBuildInfo(program, selected_device, CL_PROGRAM_BUILD_LOG, sizeof(build_log), build_log, NULL);
        fprintf(stderr, "Error in kernel: %s\n", build_log);
        exit(EXIT_FAILURE);
    }
    free(source_str);

    cl_mem bufA = clCreateBuffer(context, CL_MEM_READ_ONLY, m * m * sizeof(float), NULL, &err);
    OCL_SAFE_CALL(err);
    cl_mem bufB = clCreateBuffer(context, CL_MEM_READ_ONLY, m * m * sizeof(float), NULL, &err);
    OCL_SAFE_CALL(err);
    cl_mem bufC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, m * m * sizeof(float), NULL, &err);
    OCL_SAFE_CALL(err);

    clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0, m * m * sizeof(float), A, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0, m * m * sizeof(float), B, 0, NULL, NULL);

    cl_kernel kernel = clCreateKernel(program, "matrix_multiply", &err);
    OCL_SAFE_CALL(err);


    // Set kernel arguments
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufA);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufB);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufC);
    err |= clSetKernelArg(kernel, 3, sizeof(int), &m);
    err |= clSetKernelArg(kernel, 4, sizeof(int), &BLOCK_SIZE);
    OCL_SAFE_CALL(err);

    cout << "Starting kernel..." << endl;
    auto start = high_resolution_clock::now();


    size_t local_dims[2] = {(size_t)BLOCK_SIZE, (size_t)BLOCK_SIZE};
    size_t global_dims[2] = {(size_t)m, (size_t)m};
    clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_dims, local_dims, 0, NULL, NULL);
    OCL_SAFE_CALL(err);

    float *C = (float*)malloc(sizeof(float) * m * m);
    clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, m * m * sizeof(float), C, 0, NULL, NULL);
    OCL_SAFE_CALL(err);
    auto stop = high_resolution_clock::now();
    cout << "Kernel finished" << endl;
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Kernel duration: " << duration.count() << "ms" << endl;


    //calculate element [0][0] manually
    float sum = 0;
    for (int i = 0; i < m; ++i) {
        sum += A[i] * B[i * m];
    }
    cout << "C[0][0] = " << C[0] << endl;
    cout << "sum = " << sum << endl;

    if (abs(C[0] - sum) > 0.0001) {
        cout << "Wrong result!" << endl;
    } else {
        cout << "Correct result!" << endl;
    }

    // Release OpenCL resources
    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);

    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    // Release other OpenCL resources
    free(A);
    free(B);
    free(C);

    return 0;
}
