//
// Created by mikeasta on 06/12/23.
//

#pragma once

#include <CL/cl.h>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<int>> matrix;
    int size;
public:
    explicit Matrix(int size): size(size) {
        for (int i = 0; i < size; i++) {
            matrix.emplace_back(size);
            for (int j = 0; j < size; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    void set_value(int value, int i, int j) {
        matrix[i][j] = value;
    }

    int get_value(int i, int j) const {
        return matrix[i][j];
    }

    int get_size() const {
        return size;
    }
};


Matrix operator+(const Matrix &first, const Matrix &second) {
    Matrix result(first.get_size());

    for (int i = 0; i < first.get_size(); ++i) {
        for (int j = 0; j < second.get_size(); ++j) {
            result.set_value(first.get_value(i, j) + second.get_value(i, j), i, j);
        }
    }

    return result;
}


Matrix operator-(const Matrix &first, const Matrix &second) {
    Matrix result(first.get_size());

    for (int i = 0; i < first.get_size(); ++i) {
        for (int j = 0; j < second.get_size(); ++j) {
            result.set_value(first.get_value(i, j) - second.get_value(i, j), i, j);
        }
    }

    return result;
}


bool operator==(const Matrix &first, const Matrix &second) {
    for (int i = 0; i < first.get_size(); ++i) {
        for (int j = 0; j < second.get_size(); ++j) {
            if (first.get_value(i, j) != second.get_value(i, j))
                return false;
        }
    }

    return true;
}