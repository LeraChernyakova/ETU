#pragma once
#include <vector>

class Matrix {
    private:
        int _rows, _cols;
        std::vector<int> _matrix;
        
    public:
        Matrix(int rows = 0, int cols = 0);
        Matrix(const Matrix& other);
        Matrix& operator=(const Matrix& other);
        int getRows() const;
        int getCols() const;
        int getElem(int r, int c) const;
        int& getElem(int r, int c);
        const int *data() const;
        int *data();
};

Matrix operator*(const Matrix& m1, const Matrix& m2);
