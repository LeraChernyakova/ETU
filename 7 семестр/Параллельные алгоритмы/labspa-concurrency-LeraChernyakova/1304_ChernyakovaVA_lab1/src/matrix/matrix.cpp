#include "matrix.h"
#include "../socket/socket.h"

#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>

Matrix::Matrix(int rows, int cols)
    : rows_{rows}, cols_{cols}, data_(rows * cols, 0) {}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        cols_ = other.cols_;
        rows_ = other.rows_;
        data_ = other.data_;
    }
    return *this;
}

bool isNumber(const std::string& str, int& num) {
    try {
        num = std::stoi(str);
    } catch (...) {
        return false;
    }
    return true;
}

bool readRowsCols(int argc, char* argv[], int& rowsLeft, int& colsLeft, int& rowsRight, int& colsRight) {
    if (argc < 5) {
        return false;
    }

    if (!isNumber(argv[1], rowsLeft) ||
        !isNumber(argv[2], colsLeft) ||
        !isNumber(argv[3], rowsRight) ||
        !isNumber(argv[4], colsRight)) {
        return false;
    }

    return true;
}

Matrix createMatrix(int rowCnt, int colCnt) {
    Matrix newMatrix(rowCnt, colCnt);
    for (int row = 0; row < rowCnt; row++) {
        for (int col = 0; col < colCnt; col++) {
            newMatrix.data_[row * colCnt + col] = std::rand() % 100;
        }
    }
    return newMatrix;
}

bool sendMatrix(const Socket& socket, const Matrix& matrix) {
    int sizes[2] = {matrix.rows_, matrix.cols_};
    if (!socket.writeData(sizes, 2)) {
        throw std::runtime_error("Cannot write matrix sizes");
    }
    if (!socket.writeData(matrix.data_.data(), matrix.rows_ * matrix.cols_)) {
        throw std::runtime_error("Cannot write matrix data");
    }
    return true;
}

bool readMatrix(const Socket& socket, Matrix& matrix) {
    int sizes[2] = {matrix.rows_, matrix.cols_};
    if (!socket.readData(sizes, 2)) {
        throw std::runtime_error("Cannot read matrix sizes");
    }
    Matrix readMatrix(sizes[0], sizes[1]);
    if (!socket.readData(readMatrix.data_.data(), readMatrix.cols_ * readMatrix.rows_)) {
        throw std::runtime_error("Cannot read matrix data");
    }
    matrix = readMatrix;
    return true;
}

void printMatrix(const Matrix& matrix, const std::string& filename) {
    std::remove(filename.c_str());

    std::ofstream outputFile(filename);
    if (!outputFile) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }

    for (int row = 0; row < matrix.rows_; row++) {
        for (int col = 0; col < matrix.cols_; col++) {
            outputFile<<matrix.data_[row * matrix.cols_ + col]<<' ';
        }
        outputFile << '\n';
    }
    outputFile << '\n';
}

Matrix operator*(const Matrix& leftMatrix, const Matrix& rightMatrix) {
    Matrix resultMatrix(leftMatrix.rows_, rightMatrix.cols_);

    for (int row = 0; row < resultMatrix.rows_; row++) {
        for (int col = 0; col < resultMatrix.cols_; col++) {
            int sum = 0;
            for (int i = 0; i < leftMatrix.cols_; i++) {
                sum += leftMatrix.data_[row * leftMatrix.cols_ + i] * rightMatrix.data_[i * rightMatrix.cols_ + col];
            }
            resultMatrix.data_[row * resultMatrix.cols_ + col] = sum;
        }
    }
    return resultMatrix;
}
