#include<iostream>
#include<vector>
#include<thread>
#include<fstream>
#define MULT_THREAD_COUNT 4

using namespace std;

int calcElement(const vector<vector<int>>& left, const vector<vector<int>>& right, int i, int j);

void parallelMult(const vector<vector<int>>& left,  const vector<vector<int>>& right, vector<vector<int>>& res, const int thread_count, const int num);

class Matrix {
public:
    vector<vector<int>> matrix;
    int rows, cols;
    Matrix(int r, int c);
    Matrix() = default;
    Matrix operator* (const Matrix& other);
    Matrix(const Matrix& other);
    Matrix(const Matrix&& other);

    void operator= (const Matrix&& other);

    void printMatrix();

    friend std::ostream& operator<< (std::ostream& stream, const Matrix& m);

};