#pragma once

#include <string>
#include <CL/cl.h>

#define cl(...)    cl_assert((__VA_ARGS__), __FILE__, __LINE__, true)
#define cl_ok(err) cl_assert(err, __FILE__, __LINE__, true)

std::string clGetErrorString(cl_int err);

cl_int cl_assert(cl_int code, const std::string& file, int line, bool abort);

