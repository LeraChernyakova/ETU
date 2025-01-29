#include "../include/utils.hpp"

std::string get_program_text() {
    std::ifstream f("./kernel.cl");
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}


cl_program build_program(cl_context ctx, cl_device_id device) {
    std::string kernel_src = get_program_text();
    const char* src_text = kernel_src.data();
    size_t src_size = kernel_src.size();
    cl_program program = clCreateProgramWithSource(
        ctx,
        1,
        &src_text,
        &src_size,
        NULL
    );
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    return program;
}