#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>

const char readerSocket[] = "/tmp/read_socket";
const char writerSocket[] = "/tmp/write_socket";

class Socket;

class Matrix {
public:
    int rows_;
    int cols_;
    std::vector<int> data_;

    Matrix(int rows = 0, int cols = 0);
    Matrix& operator=(const Matrix& other);
};

bool readRowsCols(int argc, char* argv[], int& rowsLeft, int& colsLeft, int& rowsRight, int& colsRight);
Matrix createMatrix(int rows, int cols);
bool sendMatrix(const Socket& socket, const Matrix& matrix);
bool readMatrix(const Socket& socket, Matrix& matrix);
void printMatrix(const Matrix& matrix, const std::string& filename);

Matrix operator*(const Matrix& leftMatrix, const Matrix& rightMatrix);

bool isNumber(const std::string& str, int& num);

#endif //MATRIX_H
