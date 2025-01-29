#include "matrix.h"

// Конструктор, создающий матрицу заданного размера и заполняющий её случайными значениями от -10 до 10.
Matrix::Matrix(int r, int c) : rows(r), cols(c), matrix(r, std::vector<int>(c)) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
		    matrix[i][j] = rand() % 21 - 10;
	    }
    }
}

// Конструктор копирования.
Matrix::Matrix(const Matrix& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = other.matrix;
}

// Конструктор перемещения.
Matrix::Matrix(const Matrix&& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = move(other.matrix);
}

// Перегруженный оператор умножения матриц.
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

// Перегруженный оператор присваивания для rvalue.
void Matrix::operator= (const Matrix&& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = move(other.matrix);
}

// Функция для вывода матрицы в консоль.
void Matrix::printMatrix() {
    for (auto &r : matrix) {
        for (auto &el : r) {
            cout << el << ' ';
        }
        cout << '\n';
    }
}

// Перегруженный оператор вывода для потока.
std::ostream& operator<< (std::ostream& os, const Matrix& mat) {
    os << mat.rows << ' ' << mat.cols << '\n';
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            os << mat.matrix[i][j];
            if (j + 1 < mat.cols) os << ' ';
        }
        os << '\n';
    }
    return os;
}
