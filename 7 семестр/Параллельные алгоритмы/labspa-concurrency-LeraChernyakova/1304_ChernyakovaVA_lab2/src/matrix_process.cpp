#include "./matrix_process.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

Matrix createMatrix(int rows, int cols) {
    Matrix newMatrix(rows, cols);
    for (int r = 0; r < newMatrix.getRows(); r++) {
        for (int c = 0; c < newMatrix.getCols(); c++) {
            newMatrix.getElem(r, c) = std::rand() % 100;
        }
    }
    return newMatrix;
}

void printMatrix(const Matrix& matrix, const std::string& filename) {
    std::ofstream outputFile(filename, std::ios::app);
    if (!outputFile) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }

	for (int r = 0; r < matrix.getRows(); r++) {
        for (int c = 0; c < matrix.getCols(); c++) {
            outputFile << matrix.getElem(r, c) << ' ';
        }
        outputFile << '\n';
    }
    outputFile << '\n';
}

bool readInt(const std::string& str, int& num) {
    try
    {
        num = std::stoi(str);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

bool readMatrices(int argc, char *argv[], int& rows1, int& cols1, int& rows2, int& cols2) {
    if (argc < 5) {
        return false;
    }
    if (!readInt(argv[1], rows1) || !readInt(argv[2], cols1)
     || !readInt(argv[3], rows2) || !readInt(argv[4], cols2)) {
        return false;
     }
    return true;
}
