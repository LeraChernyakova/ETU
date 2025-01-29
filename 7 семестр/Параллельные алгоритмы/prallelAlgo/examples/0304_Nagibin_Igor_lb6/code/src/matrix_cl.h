#ifndef MATRIX_CL_H
#define MATRIX_CL_H

#include <CL/cl.h>
#include <libclew/ocl_init.h>
#include <string>
#include <vector>
#include "matrixfunctions.hpp"


class MatrixCl
{
public:
    MatrixCl(Matrix& m1_, Matrix& m2_, size_t workGroupSize_);
    std::vector<unsigned>& getResut();
    int isError() {return error;}
    ~MatrixCl();
private:
    int error = 0;
    size_t workGroupSize;
    size_t sideSize;
    std::vector<unsigned> matrix1, matrix2, result;
    

    cl_mem m1Buffer;
    cl_mem m2Buffer;
    cl_mem resBuffer;

    cl_device_id createDevice();
    cl_program buildProgramCL(cl_context ctx, cl_device_id device, const std::string& clFilename);
    void execute(cl_kernel kernel, cl_command_queue queue, cl_context context);
};

#endif //MATRIX_CL_H