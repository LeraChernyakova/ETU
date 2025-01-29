#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <CL/cl.h>
#include <libclew/ocl_init.h>

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
