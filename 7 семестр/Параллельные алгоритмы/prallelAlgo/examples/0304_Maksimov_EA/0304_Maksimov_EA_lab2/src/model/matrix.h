#pragma once

#include <vector>
#include <iostream>

#define MATRIX_SIZE 20
#define MATRIX_MAX_VALUE 1000

using Matrix = std::vector<std::vector<int>>;

Matrix getTransposedMatrix(Matrix matrix);
void multiplyMatrices(std::vector<Matrix>* matricesPointer);
Matrix generateMatrix();
Matrix squareMatrix(Matrix A);
