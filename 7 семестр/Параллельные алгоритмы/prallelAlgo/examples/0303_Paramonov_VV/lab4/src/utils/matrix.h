#ifndef MATRIX
#define MATRIX

#include <vector>
#include <iostream>
#include <fstream>
#include <random>


class Matrix {
    private:
        int mRows;
        int mCols;
        std::vector<std::vector<int>> matrix;

    public:
        Matrix(int rows=0, int cols=0);
        Matrix(int rows, int cols, int rndMin, int rndMax);

        Matrix(const Matrix& secondMat);
        Matrix(const Matrix&& secondMats);

        void randomInit(int rndMin, int rndMax);

        int getRows();
        int getCols();

        std::vector<int>& operator[](int index);
        Matrix operator+(const Matrix& secondMat);
        Matrix operator-(const Matrix& secondMat);
        Matrix operator*(const Matrix& secondMat);
        bool operator==(Matrix& secondMat);
        void operator=(const Matrix&& secondMat);

        static std::vector<int> multiplyRow(Matrix& firstMat, Matrix& secondMat, int rowInd);

        void printMatrix();
        void writeMatrix(std::string& fileName);
};

#endif