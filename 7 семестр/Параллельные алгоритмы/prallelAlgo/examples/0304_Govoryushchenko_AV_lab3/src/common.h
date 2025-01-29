#pragma once
#include <string>
#include "./matrix.h"

Matrix createMatrix(int rows, int cols);
void printMatrix(const Matrix& matrix);
bool readInt(const std::string& str, int& num);
bool readMatrices(int argc, char *argv[], int& rows1, int& cols1, int& rows2, int& cols2);
