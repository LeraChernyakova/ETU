#include "./matrix.h"


Matrix::Matrix(int rows, int cols)
    :_rows{rows}, _cols{cols}, _matrix(cols*rows, 0)
{}

Matrix::Matrix(const Matrix& other)
    :_rows{other._rows}, _cols{other._cols}, _matrix{other._matrix}
{}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other)
    {
        _cols = other._cols;
        _rows = other._rows;
        _matrix = other._matrix;
    }
    return *this;
}

int Matrix::getRows() const {
    return _rows;
}

int Matrix::getCols() const {
    return _cols;
}

int Matrix::getElem(int r, int c) const {
    return _matrix[r * _cols + c];
}

int& Matrix::getElem(int r, int c) {
    return _matrix[r * _cols + c];
}

const int *Matrix::data() const {
    return _matrix.data();
}

int *Matrix::data() {
    return _matrix.data();
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    Matrix resMatrix(m1.getRows(), m2.getCols());
    for (int r = 0; r < resMatrix.getRows(); r++) {
        for (int c = 0; c < resMatrix.getCols(); c++) {
            for (int i = 0; i < m1.getCols(); i++) {
                resMatrix.getElem(r, c) += m1.getElem(r, i) * m2.getElem(i, c);
            }
        }
    }
    return resMatrix;
}
