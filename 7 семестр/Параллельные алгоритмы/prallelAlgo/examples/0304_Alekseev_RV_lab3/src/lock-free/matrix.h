#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {        
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

    private:
		int _rows;
		int _cols;
        std::vector<int> _matrix;
};

Matrix operator*(const Matrix& m1, const Matrix& m2);

#endif
