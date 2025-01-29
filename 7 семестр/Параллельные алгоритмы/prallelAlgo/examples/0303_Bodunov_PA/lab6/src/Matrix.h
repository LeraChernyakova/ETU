#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <iostream>
#include <vector>
#include <fstream>
#include <CL/cl.h>
#include <string>
#include <chrono>

using namespace std;

class Matrix {
public:
    vector<cl_int> matrix;
    int rows, cols;
    Matrix(int r, int c, bool fill);
    Matrix() = default;
    Matrix(const Matrix& other);
    Matrix(const Matrix&& other);

    Matrix operator* (const Matrix& other) const;

    void operator= (const Matrix&& other) noexcept;

    bool operator==(vector<cl_int>& second_mat);

    friend std::ostream& operator<< (std::ostream& stream, const Matrix& m);

};
