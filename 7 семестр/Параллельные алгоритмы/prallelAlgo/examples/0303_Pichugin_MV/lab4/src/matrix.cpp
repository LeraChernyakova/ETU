#include "matrix.h"

// Конструктор матрицы. r - количество строк, c - количество столбцов.
// Если fill_with_vals == true, то заполняет матрицу случайными значениями от -10 до 10.
Matrix::Matrix(int r, int c, bool fill_with_vals) : rows(r), cols(c), matrix(r, std::vector<int>(c)) {
    if (fill_with_vals) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
	    	    matrix[i][j] = rand() % 21 - 10;
	        }
        }
    }
}

// Копирующий конструктор.
Matrix::Matrix(const Matrix& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = other.matrix;
}

// Перемещающий конструктор.
Matrix::Matrix(const Matrix&& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = move(other.matrix);
}

// Перегруженный оператор умножения матриц.
Matrix Matrix::operator* (const Matrix& other) const {
    Matrix result(this->rows, other.cols, false);
    if (this->rows == other.cols) {
        int tmp;
        for(int i = 0; i < this->rows; i++) {
            for(int j = 0; j < other.cols; j++) {
                tmp = 0;
                for (int k = 0; k < other.rows; k++) {
                    tmp += (this->matrix[i][k] * other.matrix[k][j]);
                }
                result.matrix[i][j] = tmp;
            }
        }
    } else {
        cout << "wrong dimensions for multiplications\n";
    }
    return result;
}

// Перегруженный оператор сложения матриц.
Matrix Matrix::operator+ (const Matrix& other) {
    Matrix result(this->rows, other.cols, false);
    if (this->rows == other.rows && this->cols == other.cols) {
        int tmp, size = this->rows;
        for(int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
            }
        }
    } else {
        cout << "Wrong dimensions for sum\n";
    }
    return result;
}

// Перегруженный оператор вычитания матриц.
Matrix Matrix::operator- (const Matrix& other) {
    Matrix result(this->rows, other.cols, false);
    if (this->rows == other.rows && this->cols == other.cols) {
        int tmp, size = this->rows;
        for(int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
            }
        }
    } else {
        cout << "Wrong dimensions for substraction\n";
    }
    return result;
}

// Перегруженный оператор присваивания с перемещением.
void Matrix::operator= (const Matrix&& other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = move(other.matrix);
}

// Перегруженный оператор сравнения матриц.
bool Matrix::operator==(const Matrix &other) {
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            if (matrix[i][j] != other.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Перегруженный оператор вывода матрицы в поток.
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
