#ifndef CL_FUNC_H
#define CL_FUNC_H

#include <cstdint>

#define CL_TARGET_OPENCL_VERSION 220
class Matrix;

constexpr std::size_t local_work_size[] = { 16, 16 };


Matrix multiply_matrices_ocl( const Matrix& lhs, const Matrix& rhs );

#endif // #ifndef CL_FUNC_H