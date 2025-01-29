#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <CL/cl.h>
#include <libclew/ocl_init.h>


cl_device_id create_device();
cl_program build_program(cl_context ctx, cl_device_id device);
std::pair<std::vector<int>, std::vector<int>> generate_task(int size);
void save_result(const int* matrix, int size);
void invoke_kernel(
    cl_kernel kernel,
    cl_command_queue queue,
    cl_mem left,
    cl_mem right,
    cl_mem kernel_result,
    cl_int* host_result,
    int size
);