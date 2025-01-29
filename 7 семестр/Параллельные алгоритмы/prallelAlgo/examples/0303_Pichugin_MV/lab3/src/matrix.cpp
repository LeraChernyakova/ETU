#include "matrix.h"



Matrix::Matrix(int r, int c) : rows(r), cols(c), matrix(r, std::vector<int>(c)) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
		    matrix[i][j] = rand() % 50 - 25;
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

Matrix Matrix::operator* (const Matrix& other) {
    
    Matrix result(this->rows, other.cols);
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < other.cols; j++) {
            result.matrix[i][j] = 0;
            for (int k = 0; k < other.rows; k++) {
                result.matrix[i][j] += (this->matrix[i][k] * other.matrix[k][j]);
            }
        }
    }
    return result;
}

void Matrix::operator= (const Matrix&& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = move(other.matrix);
}

std::ostream& operator<< (std::ostream& os, const Matrix& m) {
    os << m.rows << ' ' << m.cols << '\n';
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            os << m.matrix[i][j];
            if (j + 1 < m.cols) os << ' ';
        }
        os << '\n';
    }
    return os;
}