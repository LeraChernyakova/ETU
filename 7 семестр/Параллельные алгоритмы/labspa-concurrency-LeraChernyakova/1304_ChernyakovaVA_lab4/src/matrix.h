#ifndef MATRIX_H
#define MATRIX_H

#pragma once
#include <vector>

class Matrix {
private:
    int _rows, _cols;
    std::vector<int> _matrix;

public:
    Matrix(int rows = 0, int cols = 0);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    int getRows() const;
    int getCols() const;
    int getElem(int r, int c) const;
    int& getElem(int r, int c);

    Matrix getSubmatrix(int r, int c, int rows, int cols) const;
    void setSubmatrix(int r, int c, const Matrix& matr);

    friend bool operator==(const Matrix& m1, const Matrix& m2);
};

Matrix operator*(const Matrix& m1, const Matrix& m2);
Matrix operator-(const Matrix& m1, const Matrix& m2);
Matrix operator+(const Matrix& m1, const Matrix& m2);
bool operator==(const Matrix& m1, const Matrix& m2);

Matrix createMatrix(int rows, int cols);
Matrix parallelSimple(const Matrix& m1, const Matrix& m2, int thCount);
Matrix parallelBlocks(const Matrix& m1, const Matrix& m2, int thCount);
Matrix padMatrix(const Matrix& m, int newSize);
Matrix trimMatrix(const Matrix& m, int originalRows, int originalCols);
Matrix strassenMatrixMult(const Matrix& m1, const Matrix& m2);

#endif //MATRIX_H
