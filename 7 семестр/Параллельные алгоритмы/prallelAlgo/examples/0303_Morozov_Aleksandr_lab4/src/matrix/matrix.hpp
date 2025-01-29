#include <vector>
#include <cstdlib>
#include <fstream>
#pragma once

class Matrix {
public:
    std::vector<std::vector<int>> matrix;
    int elements;
    Matrix(int size);
    static Matrix empty_matrix(int size);
    friend std::ofstream& operator<<(std::ofstream& out, Matrix& matrix);
    friend Matrix operator*(const Matrix &left, const Matrix &right);
    friend Matrix operator+(const Matrix &left, const Matrix &right);
    friend Matrix operator-(const Matrix &left, const Matrix &right);
    Matrix();
};