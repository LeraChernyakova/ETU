#include "matrix.h"



Matrix::Matrix() {};

Matrix::Matrix(int N, int M) : rows(N), cols(M), matrix(N* M)
{
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<> distrib(0, 9);
    //std::cout << "|||||Начало создания|||||" <<std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = distrib(generator);
        }
    }
    //  std::cout << "|||||Конец создания|||||" <<std::endl;


}

Matrix::Matrix(const Matrix& second) {
    this->rows = second.rows;
    this->cols = second.cols;
    this->matrix = second.matrix;
}

Matrix::Matrix(const Matrix&& second) {
    this->rows = second.rows;
    this->cols = second.cols;
    this->matrix = move(second.matrix);
}

const char* Matrix::compare(const Matrix&& second) {
    for (int i = 0; i < second.matrix.size(); i++) {
        if (this->matrix[i] != second.matrix[i]) {
            return "Fail";
        }
    }
    return "Success";
   }

Matrix Matrix::operator* (const Matrix& second) const {

    Matrix result(this->rows, second.cols);
    if (this->cols == second.rows) {
        int tmp;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < second.cols; j++) {
                tmp = 0;
                for (int k = 0; k < second.rows; k++) {
                    tmp += (this->matrix[i * this->cols + k] * second.matrix[k * second.cols + j]);
                }
                result.matrix[i * second.cols + j] = tmp;
            }
        }
    }
    return result;
}

void Matrix::operator= (const Matrix&& second) noexcept {
    this->rows = second.rows;
    this->cols = second.cols;
    this->matrix = move(second.matrix);
}


std::ostream& operator<<(std::ostream& out, const Matrix& matrix) // вывод в консоль
{
    out << matrix.rows << ' ' << matrix.cols << '\n';
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            out << matrix.matrix[i * matrix.cols + j];
            if (j + 1 < matrix.cols) {
                out << ' ';
            }
        }
        out << '\n';
    }
    return out;
}