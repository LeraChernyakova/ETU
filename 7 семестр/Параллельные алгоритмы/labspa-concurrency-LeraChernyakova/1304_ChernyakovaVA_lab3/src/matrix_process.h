#pragma once
#include <string>
#include <fstream>
#include "./matrix.h"

Matrix createMatrix(int rows, int cols);
void printMatrix(const Matrix& matrix, const std::string& filename);
bool readInt(const std::string& str, int& num);
bool readMatrices(int argc, char *argv[], int& rows1, int& cols1, int& rows2, int& cols2);
