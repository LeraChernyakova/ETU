#include "matrix.hpp"


Matrix::Matrix(int size) {
    this->matrix = std::vector(size, std::vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            this->matrix[i][j] = -10 + rand() % 21;
        }
    }
}

Matrix::Matrix(std::vector<std::vector<int>> m) {
    int size = m.size();
    this->matrix = std::vector(size, std::vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            this->matrix[i][j] = m[i][j];
        }
    }
}

Matrix operator*(const Matrix &left, const Matrix &right) {
    int size = left.matrix.size();
    auto m = std::vector(size, std::vector<int>(size));
    int tmp_sum;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tmp_sum = 0;
            for (int k = 0; k < size; k++) {
                tmp_sum += (left.matrix[i][k] * right.matrix[k][j]);
            }
            m[i][j] = tmp_sum;
        }
    }
    return Matrix(m);
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