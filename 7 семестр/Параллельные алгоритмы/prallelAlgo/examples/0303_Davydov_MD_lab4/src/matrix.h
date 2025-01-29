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
    void multipleExtend(Matrix& second,Matrix& result,int startRow,int endRow);
    Matrix operator=(Matrix copy);
    void transp(Matrix& mat);
    friend Matrix operator+(Matrix first,Matrix second);
    friend Matrix operator*(Matrix first,Matrix second);
    friend Matrix operator-(Matrix first,Matrix second);
    void fileOutput(std::string fileName);
    friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix);
};

#endif // MATRIX_H
