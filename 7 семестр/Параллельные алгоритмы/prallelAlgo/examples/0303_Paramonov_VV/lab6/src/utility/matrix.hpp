#ifndef MATRIX
#define MATRIX

#include <vector>
#include <iostream>
#include <fstream>
#include <random>


class Matrix {
    private:
        int m_rows;
        int m_cols;
        std::vector<int> matrix;

    public:
        Matrix(int rows=0, int cols=0);
        Matrix(int rows, int cols, int rndMin, int rndMax);

        Matrix(const Matrix& second_mat);
        Matrix(const Matrix&& secondMats);

        void random_init(int rndMin, int rndMax);

        int getRows();
        int getCols();

        int& operator() (int row_ind, int col_ind);
        int  operator() (int row_ind, int col_ind) const;
        Matrix operator+(const Matrix& second_mat);
        Matrix operator-(const Matrix& second_mat);
        Matrix operator*(const Matrix& second_mat);
        bool operator==(Matrix& second_mat);
        void operator=(const Matrix&& second_mat);

        void print_matrix();
        void write_matrix(std::string& file_name);

        int* to_pointer();
};

#endif