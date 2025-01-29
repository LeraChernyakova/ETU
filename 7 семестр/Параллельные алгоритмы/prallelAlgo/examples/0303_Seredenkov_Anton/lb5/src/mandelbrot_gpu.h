#pragma once
#include "additional.h"

std::string get_program_text();
cl_program build_program(cl_context ctx, cl_device_id device);
cl_device_id get_device();
void invoke_kernel(cl_kernel kernel, cl_command_queue queue, cl_mem buffer, cl_uint* result, int w, int h, float iters);