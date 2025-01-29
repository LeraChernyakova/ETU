#ifndef MATRIX
#define MATRIX

#include <vector>
#include <iostream>
#include <fstream>
#include <random>


class Matrix {
    private:
        std::vector<std::vector<int>> matrix;
        int mRows;
        int mCols;

    public:
        Matrix(int rows=0, int cols=0);
        Matrix(int rows, int cols, int rndMin, int rndMax);

        static std::vector<int> multiplyRow(Matrix& firstMat, Matrix& secondMat, int rowNum);
        void printMatrix();
        int* serialize();
        void deserialize(int* buf);
        void writeMatrix(std::string& fileName);

        int getRows();
        int getCols();

        void setRow(int rowNum, std::vector<int>& row);

        void randomInit(int rndMin, int rndMax);
};

#endif