#pragma once
#include <vector>
#include <utility>
#include <iostream>

#include <CL/cl.h>
struct Matrix
{
    std::pair<unsigned int, unsigned int> size;
    std::vector<cl_int> m;
    static Matrix generate(int size);
};
