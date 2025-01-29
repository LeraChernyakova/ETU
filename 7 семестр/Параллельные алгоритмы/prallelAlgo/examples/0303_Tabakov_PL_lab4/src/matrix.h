#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <cstdlib>
#include <fstream>

class Matrix {
public:
    std::vector<std::vector<int>> matrix;
    Matrix(int MATRIX_SIZE);
    Matrix(int MATRIX_SIZE, bool zeros);
    Matrix(std::vector<std::vector<int>> matrix);
    friend Matrix operator*(const Matrix &matrixA, const Matrix &matrixB);
    friend Matrix operator+(const Matrix &matrixA, const Matrix &matrixB);
    friend Matrix operator-(const Matrix &matrixA, const Matrix &matrixB);
    friend Matrix operator==(Matrix &matrixA, Matrix &matrixB);
    friend std::ofstream& operator<<(std::ofstream& out, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& out, Matrix& matrix);
};

#endif // MATRIX_H

