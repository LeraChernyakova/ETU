//
// Created by mikeasta on 11/20/23.
//
#pragma once

#include <vector>
#include <iostream>
#include <stdlib.h>

class Matrix {
public:
    std::vector<std::vector<int>> data;
    int _rows = 0;
    int _cols = 0;

    Matrix(int rows, int cols): _rows(rows), _cols(cols) {
        data.resize(rows);
        std::fill(data.begin(), data.end(), std::vector<int>(cols));
    }

    int rows() const {
        return _rows;
    }

    int cols() const {
        return _cols;
    }

    // Get slice of matrix
    Matrix slice(int rowsAmount, int colsAmount, int startRow, int startCol) const {
        Matrix ans(rowsAmount, colsAmount);
        for (size_t i = 0; i < rowsAmount; i++) {
            size_t row = i + startRow;
            for (size_t j = 0; j < colsAmount; j++) {
                ans.data[i][j] = this->data[row][j + startCol];
            }
        }
        return ans;
    }

    // Insert data from source matrix
    void insert(const Matrix& src, int startRow, int startCol) {
        for (size_t i = 0; i < src.rows(); i++) {
            int row = i + startRow;
            for (size_t j = 0; j < src.cols(); j++) {
                data[row][j + startCol] = src.data[i][j];
            }
        }
    }

    // Fill matrix with random values
    void fill(int min = 0, int max = 10) {
        for (size_t i = 0; i < rows(); i++) {
            for (size_t j = 0; j < cols(); j++) {
                data[i][j] = rand() % (max - min + 1) + min;
            }
        }
    }

    // Matrix logging
    void log() const {
        for (size_t i = 0; i < rows(); i++) {
            for (size_t j = 0; j < cols(); j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Operators
    Matrix operator + (const Matrix& secondMatrix) const {
        Matrix ans (rows(), cols());
        for (size_t i = 0; i < rows(); i++) {
            for (size_t j = 0; j < cols(); j++) {
                ans.data[i][j] = data[i][j] + secondMatrix.data[i][j];
            }
        }
        return ans;
    }

    Matrix operator - (const Matrix& secondMatrix) const {
        Matrix ans (rows(), cols());
        for (size_t i = 0; i < rows(); i++) {
            for (size_t j = 0; j < cols(); j++) {
                ans.data[i][j] = data[i][j] - secondMatrix.data[i][j];
            }
        }
        return ans;
    }
};