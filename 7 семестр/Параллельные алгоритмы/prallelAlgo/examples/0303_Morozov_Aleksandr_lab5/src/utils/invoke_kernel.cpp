#include "../include/utils.hpp"


int align(int x, int y) {
    return (x + y - 1) / y * y;
}


void invoke_kernel(
    cl_kernel kernel,
    cl_command_queue queue,
    cl_mem buffer,
    cl_uint* result,
    int w,
    int h,
    float iters 
) {
    clSetKernelArg(kernel, 0, sizeof(float), &iters);
    clSetKernelArg(kernel, 1, sizeof(cl_int), &w);
    clSetKernelArg(kernel, 2, sizeof(cl_int), &h);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &buffer);
    size_t local_size[2] = {256, 1};
    size_t global_size[2] = {
        align(w, local_size[0]),
        align(h, local_size[1])
    };
    clEnqueueNDRangeKernel(
        queue,
        kernel,
        2,
        NULL,
        global_size,
        local_size,
        0,
        NULL,
        NULL
    );
    clEnqueueReadBuffer(
        queue,
        buffer,
        CL_TRUE,
        0,
        sizeof(int) * w * h,
        result,
        0,
        NULL,
        NULL
    );
    clFinish(queue);
}