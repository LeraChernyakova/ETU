#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>


class Matrix
{
public:
    std::vector<std::vector<long long int>> matrix;
    Matrix();
    Matrix(int N, int M);
    void multiple(Matrix& second,Matrix& result);
    void multiple(Matrix& second,Matrix& result,int shiftRow,int threadCount);
    void multipleExtend(Matrix& second,Matrix& result,int startRow,int endRow);
    int*  toArray();
    void fromArray(int* buf,int  N,int M);
    void fileOutput(char* fileName);
    Matrix operator=(Matrix copy);
    void transp(Matrix& mat);
    friend Matrix operator+(Matrix first,Matrix second);
    friend Matrix operator*(Matrix first,Matrix second);
    friend Matrix operator-(Matrix first,Matrix second);
    friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix);
};

#endif // MATRIX_H
