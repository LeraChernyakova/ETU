#include "./matrix.h"
#include <cstdlib>
#include <thread>


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

Matrix Matrix::getSubmatrix(int r, int c, int rows, int cols) const {
    Matrix result(rows, cols);
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            result.getElem(row, col) = getElem(r + row, c + col);
        }
    }
    return result;
}

void Matrix::setSubmatrix(int r, int c, const Matrix& matr) {
    for (int row = 0; row < matr.getRows(); row++) {
        for (int col = 0; col < matr.getCols(); col++) {
            getElem(r + row, c + col) = matr.getElem(row, col);
        }
    }
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

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix resMatrix(m1.getRows(), m2.getCols());
    for (int r = 0; r < resMatrix.getRows(); r++) {
        for (int c = 0; c < resMatrix.getCols(); c++) {
            resMatrix.getElem(r, c) = m1.getElem(r, c) + m2.getElem(r, c);
        }
    }
    return resMatrix;
}

Matrix operator-(const Matrix& m1, const Matrix& m2) {
    Matrix resMatrix(m1.getRows(), m2.getCols());
    for (int r = 0; r < resMatrix.getRows(); r++) {
        for (int c = 0; c < resMatrix.getCols(); c++) {
            resMatrix.getElem(r, c) = m1.getElem(r, c) - m2.getElem(r, c);
        }
    }
    return resMatrix;
}

bool operator==(const Matrix& m1, const Matrix& m2) {
    if (m1.getCols() == m2.getCols() && m1.getRows() == m2.getRows()) {
        return m1._matrix == m2._matrix;
    }
    return false;
}

Matrix createMatrix(int rows, int cols) {
    Matrix newMatrix(rows, cols);
    for (int r = 0; r < newMatrix.getRows(); r++) {
        for (int c = 0; c < newMatrix.getCols(); c++) {
            newMatrix.getElem(r, c) = std::rand() % 100;
        }
    }
    return newMatrix;
}

void multiplyMatrix(const Matrix& m1, const Matrix& m2, int pCount,
                    int curIndex, Matrix& resultMatrix){
    for (int r = 0; r < resultMatrix.getRows(); r++) {
        for (int c = 0; c < resultMatrix.getCols(); c++) {
            for (int i = 0; i < m1.getCols(); i++) {
                if ((r + c) % pCount == curIndex) {
                    resultMatrix.getElem(r, c) += m1.getElem(r, i) * m2.getElem(i, c);
                }
            }
        }
    }
}

Matrix parallelMatrixMult(const Matrix& m1, const Matrix& m2, int p) {
    Matrix resultMatrix(m1.getRows(), m2.getCols());
    std::vector<std::thread> threads;
    threads.reserve(p);
    for (int i = 0; i < p; i++) {
        threads.emplace_back(multiplyMatrix, std::cref(m1), std::cref(m2),
            p, i, std::ref(resultMatrix));
    }
    for (int i = 0; i < p; i++) {
        threads[i].join();
    }
    return resultMatrix;
}

void strassenRecursive(const Matrix& m1, const Matrix& m2, Matrix& result, bool threaded) {
    int size = m1.getCols() / 2;

    if (size <= 4) {
        result = m1 * m2;
        return;
    }

    Matrix a11 = m1.getSubmatrix(0, 0, size, size);
    Matrix a12 = m1.getSubmatrix(0, size, size, size);
    Matrix a21 = m1.getSubmatrix(size, 0, size, size);
    Matrix a22 = m1.getSubmatrix(size, size, size, size);

    Matrix b11 = m2.getSubmatrix(0, 0, size, size);
    Matrix b12 = m2.getSubmatrix(0, size, size, size);
    Matrix b21 = m2.getSubmatrix(size, 0, size, size);
    Matrix b22 = m2.getSubmatrix(size, size, size, size);

    Matrix d(size, size), d1(size, size), d2(size, size),
        h1(size, size), h2(size, size),
        v1(size, size), v2(size, size);

    if (threaded) {
        std::thread t1(strassenRecursive, a11 + a22, b11 + b22, std::ref(d), false);
        std::thread t2(strassenRecursive, a12 - a22, b21 + b22, std::ref(d1), false);
        std::thread t3(strassenRecursive, a21 - a11, b11 + b12, std::ref(d2), false);
        std::thread t4(strassenRecursive, a11 + a12, std::cref(b22), std::ref(h1), false);
        std::thread t5(strassenRecursive, a21 + a22, std::cref(b11), std::ref(h2), false);
        std::thread t6(strassenRecursive, std::cref(a22), b21 - b11, std::ref(v1), false);
        std::thread t7(strassenRecursive, std::cref(a11), b12 - b22, std::ref(v2), false);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
    } else {
        strassenRecursive(a11 + a22, b11 + b22, d, false);
        strassenRecursive(a12 - a22, b21 + b22, d1, false);
        strassenRecursive(a21 - a11, b11 + b12, d2, false);
        strassenRecursive(a11 + a12, b22, h1, false);
        strassenRecursive(a21 + a22, b11, h2, false);
        strassenRecursive(a22, b21 - b11, v1, false);
        strassenRecursive(a11, b12 - b22, v2, false);
    }
    result.setSubmatrix(0, 0, d + d1 + v1 - h1);
    result.setSubmatrix(0, size, v2 + h1);
    result.setSubmatrix(size, 0, v1 + h2);
    result.setSubmatrix(size, size, d + d2 + v2 - h2);
}

Matrix strassenMatrixMult(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1.getRows(), m2.getCols());
    strassenRecursive(m1, m2, result, true);
    return result;
}
