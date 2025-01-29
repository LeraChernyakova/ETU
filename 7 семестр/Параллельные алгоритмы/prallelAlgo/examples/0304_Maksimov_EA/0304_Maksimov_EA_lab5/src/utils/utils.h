#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <CL/cl.h>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <libclew/ocl_init.h>

std::string getProgramText();
cl_program buildProgram(cl_context ctx, cl_device_id device);
cl_device_id createDevice();

void invokeKernel(
    cl_kernel kernel, cl_command_queue queue, cl_mem buffer, cl_uint* result,
    int w, int h,
    float iters
);
