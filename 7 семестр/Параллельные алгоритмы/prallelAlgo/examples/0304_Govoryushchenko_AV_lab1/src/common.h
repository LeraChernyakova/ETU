#pragma once
#include <string>
#include "./matrix.h"

class Socket;

const char readerSocket[] = "/tmp/read_socket";
const char executorSocket[] = "/tmp/write_socket";

Matrix createMatrix(int rows, int cols);
void printMatrix(const Matrix& matrix);
bool readInt(const std::string& str, int& num);
bool readMatrices(int argc, char *argv[], int& rows1, int& cols1, int& rows2, int& cols2);
bool sendMatrix(const Socket& socket, const Matrix& matr);
bool receiveMatrix(const Socket& socket, Matrix& matr);
