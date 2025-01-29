#ifndef MULTIPLY
#define MULTIPLY

#include "../utility/defines.hpp"

#include <vector>
#include <thread>
#include <CL/cl.h>
#include <tbb/task_group.h>

#include "../utility/matrix.hpp"


void strassen_mul(Matrix first, Matrix second, Matrix& result, int recursion_depth, int allow_recursion_depth);
void opencl_mul(Matrix first, Matrix second, Matrix& result, size_t* local_size, size_t* global_size);

#endif