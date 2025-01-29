#ifndef MATRIX_H
#define MATRIX_H
#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>
#include <CL/cl.h>

class Matrix
{
public:
    std::vector<cl_int> matrix;
    int rows, cols;
    Matrix();
    Matrix(int N, int M);
    Matrix(const Matrix& other);
    Matrix(const Matrix&& other);
    Matrix operator* (const Matrix& second) const;
    void operator= (const Matrix&& second) noexcept;
    const char* compare(const Matrix&& second);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
};

#endif // MATRIX_H