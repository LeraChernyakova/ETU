#include "../include/utils.hpp"


size_t align(int x, int y) {
    return (x + y - 1) / y * y;
}


void invoke_kernel(
    cl_kernel kernel,
    cl_command_queue queue,
    cl_mem left,
    cl_mem right,
    cl_mem kernel_result,
    cl_int* host_result,
    int size
) {
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &left);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &right);
    clSetKernelArg(kernel, 2, sizeof(int), &size);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &kernel_result);
    size_t local_size[2] = {16, 16};
    size_t global_size[2] = {
        align(size, local_size[0]),
        align(size, local_size[1])
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
        kernel_result,
        CL_TRUE,
        0,
        sizeof(int) * size * size,
        host_result,
        0,
        NULL,
        NULL
    );
    clFinish(queue);
}