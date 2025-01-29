#include<iostream>
#include<vector>
#include<thread>
#include<fstream>

using namespace std;

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
    friend std::ostream& operator<< (std::ostream& stream, const Matrix& m);

};