#pragma once

#include <vector>
#include <cassert>
#include <iostream>
#include <random>

using namespace std;

class Matrix {
public:
    vector<vector<int>> data;
    int _rows = 0;
    int _columns = 0;

    Matrix(int rows, int columns): _rows(rows), _columns(columns) {
        data.resize(rows);
        std::fill(data.begin(), data.end(), vector<int>(columns));
    }

    int rows() const {
        return _rows;
    }

    int columns() const {
        return _columns;
    }

    Matrix slice(int amountRow, int amountCol, int startRow, int startCol) const {
#ifdef DEBUG
        assert(startRow + amountRow <= rows());
        assert(startCol + amountCol <= columns());
#endif

        Matrix result(amountRow, amountCol);
        for (int i = 0; i < amountRow; ++i) {
            int row = i + startRow;
            for (int j = 0; j < amountCol; ++j) {
                result.data[i][j] = this->data[row][j + startCol];
            }
        }
        return result;
    }

    void insert(const Matrix& src, int startRow, int startCol) {
#ifdef DEBUG
        assert(startRow + src.rows() <= rows());
        assert(startCol + src.columns() <= columns());
#endif

        for (int i = 0; i < src.rows(); ++i) {
            int row = startRow + i;
            for (int j = 0; j < src.columns(); ++j) {
                data[row][startCol + j] = src.data[i][j];
            }
        }
    }

    void fillMatrix() {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 50);

        for (int i = 0; i < rows(); i++) {
            for (int j = 0; j < columns(); j++) {
                data[i][j] = dist6(rng) + 1;
            }
        }
    }

    void printMatrix() const {
        for (int i = 0; i < rows(); i++) {
            for (int j = 0; j < columns(); j++) {
                cout << data[i][j] << ' ';
            }
            cout << '\n';
        }
    }

    Matrix operator+(const Matrix& secondMatrix) const {
        Matrix result (rows(), columns());
        for (int i = 0; i < rows(); ++i) {
            for (int j = 0; j < columns(); ++j) {
                result.data[i][j] = data[i][j] + secondMatrix.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& secondMatrix) const {
        Matrix result (rows(), columns());
        for (int i = 0; i < rows(); ++i) {
            for (int j = 0; j < columns(); ++j) {
                result.data[i][j] = data[i][j] - secondMatrix.data[i][j];
            }
        }
        return result;
    }
};