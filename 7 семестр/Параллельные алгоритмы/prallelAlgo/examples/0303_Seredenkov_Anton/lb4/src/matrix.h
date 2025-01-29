#include<iostream>
#include<vector>
#include<thread>
#include<fstream>

using namespace std;

class Matrix {
public:
    vector<vector<int>> matrix;
    int rows, cols;
    Matrix(int r, int c, bool fill_with_vals);
    Matrix() = default;
    Matrix(const Matrix& other);
    Matrix(const Matrix&& other);

    Matrix operator* (const Matrix& other) const;
    
    Matrix operator+ (const Matrix& other);

    Matrix operator- (const Matrix& other);

    void operator= (const Matrix&& other);

    bool operator== (const Matrix& other);

    friend std::ostream& operator<< (std::ostream& stream, const Matrix& m);

};