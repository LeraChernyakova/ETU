//
// Created by dima on 18.11.23.
//

#ifndef LAB5_MANDELBROT_H
#define LAB5_MANDELBROT_H
#include <string>
#include <vector>
#include <algorithm>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <array>

#include <CL/cl.h>
#include <libclew/ocl_init.h>
cl_device_id createDevice();
void execute(cl_kernel kernel, cl_command_queue queue, cl_mem buffer, cl_uint* resultPointer, float ratio, cl_int width, cl_int height, cl_int iterLimit);
cl_program buildProgramCL(cl_context ctx, cl_device_id device, const std::string& clFilename);
std::vector<unsigned int> computeMandelbrot(int height, int width, float ratio, int iterLimit);

#endif //LAB5_MANDELBROT_H
