#ifndef MANDELBROTCOMPUTER_H
#define MANDELBROTCOMPUTER_H

#include <CL/cl.h>
#include <libclew/ocl_init.h>
#include <string>
#include <vector>


class MandelbrotComputer
{
public:
    MandelbrotComputer(size_t height, size_t width, float ratio, size_t iterLimit);
    std::vector<unsigned> get(){return std::move(pixelsBuffer);}
    int isError() {return error;}
    ~MandelbrotComputer();
private:
    int error = 0;
    size_t height, width, iterLimit;
    float ratio;
    std::vector<unsigned> pixelsBuffer;

    cl_device_id createDevice();
    cl_program buildProgramCL(cl_context ctx, cl_device_id device, const std::string& clFilename);
    void execute(cl_kernel kernel, cl_command_queue queue, cl_mem buffer,
        cl_uint* resultPointer, float ratio, cl_int width, cl_int height,
        cl_int iterLimit);
    void computeMandelbrot();
};

#endif