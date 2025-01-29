#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <CL/cl.h>
#include <libclew/ocl_init.h>


cl_device_id create_device();
cl_program build_program(cl_context ctx, cl_device_id device);
void save_result(const cl_uint* pixels, int w, int h);
void invoke_kernel(
    cl_kernel kernel,
    cl_command_queue queue,
    cl_mem buffer,
    cl_uint* result,
    int w,
    int h,
    float iters 
);