#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <cstdlib>
#include <fstream>

class Matrix {
public:
    std::vector<std::vector<int>> matrix;
    Matrix(int MATRIX_SIZE);
    Matrix(std::vector<std::vector<int>> matrix);
    friend Matrix operator*(const Matrix &matrixA, const Matrix &matrixB);
    friend std::ofstream& operator<<(std::ofstream& out, Matrix& matrix);
};

#endif // MATRIX_H
