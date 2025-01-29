#include "../include/utils.hpp"


cl_device_id create_device() {
    cl_platform_id platform;
    cl_device_id device;
    cl_uint platformsCount = 0;
    clGetPlatformIDs(0, nullptr, &platformsCount);
    std::vector<cl_platform_id> platforms(platformsCount);
    clGetPlatformIDs(platformsCount, platforms.data(), nullptr);
    clGetDeviceIDs(platforms[1], CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    return device;
}