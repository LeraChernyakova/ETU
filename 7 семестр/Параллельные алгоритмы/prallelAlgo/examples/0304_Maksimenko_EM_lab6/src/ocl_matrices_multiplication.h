#pragma once

#ifndef OCL_MATRICES_MULTIPLICATION_H
#define OCL_MATRICES_MULTIPLICATION_H

#define CL_TARGET_OPENCL_VERSION 300

#include <CL/cl.h>
#include <string>
#include <vector>
#include <memory>

namespace ocl
{

class OclMatricesMultiplication
{

private:
    bool initialized_;
    cl_device_id device_ = 0;
    cl_context context_ = 0;
    cl_command_queue command_queue_ = 0;
    std::vector< cl_mem > buffers_;
    cl_program program_ = 0;
    cl_kernel kernel_ = 0;
    size_t real_data_size_[ 2 ];
    size_t global_work_size_[ 2 ];
    static constexpr size_t local_work_size_[ 2 ] = { 16, 16 };

public:
    OclMatricesMultiplication();
    ~OclMatricesMultiplication();

    bool init( const size_t lhs_w, const size_t common_size, const size_t rhs_h
             , int32_t* lhs_data, int32_t* rhs_data );
    void deinit();
    std::unique_ptr< int32_t[] > process();

private:
    void create_context();
    void create_command_queue();
    cl_mem create_buffer( cl_mem_flags mem_flags, size_t mem_size, void* host_ptr = nullptr );
    void create_program( const std::string& file, const std::string& kernel_name );
    static size_t align( const size_t size, const size_t base );
    static void process_rc( cl_int rc, const std::string& filename, size_t line );

}; // class OclMatricesMultiplication

} // namespace ocl

#endif // OCL_MATRICES_MULTIPLICATION_H
