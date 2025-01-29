#include "matrix.hpp"

Matrix::Matrix(){}

Matrix::Matrix(int size) {
    this->elements = size * size;
    this->matrix = std::vector(size, std::vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            this->matrix[i][j] = -10 + rand() % 21;
        }
    }
}

Matrix Matrix::empty_matrix(int size) {
    Matrix matrix;
    matrix.elements = size * size;
    matrix.matrix.resize(size);
    for (int i = 0; i < size; i++) {
        matrix.matrix[i].resize(size);
    }
    return matrix;
}

std::ofstream& operator<<(std::ofstream& out, Matrix& matrix) {
    for (int i = 0; i < matrix.matrix.size(); i++) {
        for (int j = 0; j < matrix.matrix[i].size(); j++) {
            out << matrix.matrix[i][j] << " ";
        }
        out << std::endl;
    }
    out << std::endl;
    return out;
}

Matrix operator*(const Matrix &left, const Matrix &right) {
    int size = left.matrix.size();
    Matrix result = Matrix::empty_matrix(size);
    int tmp_sum;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tmp_sum = 0;
            for (int k = 0; k < size; k++) {
                tmp_sum += (left.matrix[i][k] * right.matrix[k][j]);
            }
            result.matrix[i][j] = tmp_sum;
        }
    }
    return result;
}

Matrix operator+(const Matrix &left, const Matrix &right) {
    int size = left.matrix.size();
    Matrix result = Matrix::empty_matrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.matrix[i][j] = left.matrix[i][j] + right.matrix[i][j];
        }
    }
    return result;
}

Matrix operator-(const Matrix &left, const Matrix &right) {
    int size = left.matrix.size();
    Matrix result = Matrix::empty_matrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.matrix[i][j] = left.matrix[i][j] - right.matrix[i][j];
        }
    }
    return result;
}