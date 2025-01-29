#define CL_HPP_TARGET_OPENCL_VERSION 200
#include<iostream>
#include<vector>
#include<thread>
#include<fstream>
#include<CL/opencl.hpp>

using namespace std;


class Matrix {
public:
    vector<cl_int> matrix;
    int rows, cols;
    Matrix(int r, int c, bool fill_with_vals);
    Matrix() = default;
    Matrix(const Matrix& other);
    Matrix(const Matrix&& other);

    Matrix operator* (const Matrix& other) const;

    void operator= (const Matrix&& other) noexcept;

    friend std::ostream& operator<< (std::ostream& stream, const Matrix& m);

};