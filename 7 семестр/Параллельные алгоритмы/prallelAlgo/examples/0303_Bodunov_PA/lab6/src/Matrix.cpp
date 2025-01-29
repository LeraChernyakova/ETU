#include "Matrix.h"

Matrix::Matrix(int r, int c, bool fill) : rows(r), cols(c), matrix(r * c) {
    if (fill) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i * cols + j] = rand() % 100;
            }
        }
    }
}


Matrix::Matrix(const Matrix& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = other.matrix;
}


Matrix::Matrix(const Matrix&& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = move(other.matrix);
}


Matrix Matrix::operator* (const Matrix& other) const {
    Matrix res(this->rows, other.cols, false);

    if (this->cols == other.rows) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                res.matrix[i * other.cols + j] = 0;
                for (int k = 0; k < other.rows; k++) {
                    res.matrix[i * other.cols + j] += (this->matrix[i * this->cols + k] * other.matrix[k * other.cols + j]);
                }
            }
        }
    }
    return res;
}


void Matrix::operator= (const Matrix&& other) noexcept {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = move(other.matrix);
}


bool Matrix::operator==(vector<cl_int>& other){
    if (this->matrix.size() != other.size())
        return false;

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (this->matrix[i * this->cols + j] != other[i * this->cols + j]) {
                return false;
            }
        }
    }
    return true;
}


std::ostream& operator<< (std::ostream& os, const Matrix& m) {
    os << m.rows << ' ' << m.cols << '\n';
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            os << m.matrix[i * m.cols + j];
            if (j + 1 < m.cols)
                os << ' ';
        }
        os << '\n';
    }
    return os;
}