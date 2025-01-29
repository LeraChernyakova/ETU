#include "./common.h"
#include "./socket.h"
#include <cstdlib>
#include <iostream>

Matrix createMatrix(int rows, int cols) {
    Matrix newMatrix(rows, cols);
    for (int r = 0; r < newMatrix.getRows(); r++) {
        for (int c = 0; c < newMatrix.getCols(); c++) {
            newMatrix.getElem(r, c) = std::rand() % 100;
        }
    }
    return newMatrix;
}

void printMatrix(const Matrix& matrix) {
    for (int r = 0; r < matrix.getRows(); r++) {
        for (int c = 0; c < matrix.getCols(); c++) {
            std::cout << matrix.getElem(r, c) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

bool readInt(const std::string& str, int& num) {
    try
    {
        num = std::stoi(str);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

bool readMatrices(int argc, char *argv[], int& rows1, int& cols1, int& rows2, int& cols2) {
    if (argc < 5) {
        return false;
    }
    if (!readInt(argv[1], rows1) || !readInt(argv[2], cols1) 
     || !readInt(argv[3], rows2) || !readInt(argv[4], cols2)) {
        return false;
    }
    return true;
}

bool sendMatrix(const Socket& socket, const Matrix& matr) {
    int sizes[2] = {matr.getRows(), matr.getCols()};
    if (!socket.write(sizes, 2)) {
        std::cout << "Cannot write matrix sizes\n";
        return false;
    }
    if (!socket.write(matr.data(), matr.getCols() * matr.getRows())) {
        std::cout << "Cannot write matrix data\n";
        return false;
    }
    return true;
}

bool receiveMatrix(const Socket& socket, Matrix& matr) {
    int sizes[2] = {matr.getRows(), matr.getCols()};
    if (!socket.read(sizes, 2)) {
        std::cout << "Cannot read matrix sizes\n";
        return false;
    }
    Matrix result(sizes[0], sizes[1]);
    if (!socket.read(result.data(), result.getCols() * result.getRows())) {
        std::cout << "Cannot read matrix data\n";
        return false;
    }
    matr = result;
    return true;
}
