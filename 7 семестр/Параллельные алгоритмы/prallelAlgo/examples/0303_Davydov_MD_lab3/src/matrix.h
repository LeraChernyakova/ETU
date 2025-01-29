#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <random>
#include <fstream>
#include <iostream>


class Matrix
{
public:
    std::vector<std::vector<int>> matrix;
    Matrix();
    Matrix(int N, int M);
    void multiple(Matrix& second,Matrix& result);
    void multiple(Matrix& second,Matrix& result,int shiftRow,int threadCount);
    void fileOutput(char* fileName);
    friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix);
};

#endif // MATRIX_H
