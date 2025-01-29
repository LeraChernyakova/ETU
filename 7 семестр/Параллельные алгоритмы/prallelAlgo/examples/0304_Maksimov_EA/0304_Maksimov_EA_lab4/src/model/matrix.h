#pragma once

#include <vector>
#include <iostream>

#define MATRIX_MAX_VALUE 100

using Matrix = std::vector<std::vector<int>>;

Matrix getTransposedMatrix(Matrix matrix);
int multiplyVectors(std::vector<int> a, std::vector<int> b);
void multiplyMatrices(std::vector<Matrix>* matricesPointer);
Matrix generateMatrix(int rows);

void printMatrix(Matrix A);
Matrix operator+(Matrix A, Matrix B);
Matrix operator-(Matrix A, Matrix B);
