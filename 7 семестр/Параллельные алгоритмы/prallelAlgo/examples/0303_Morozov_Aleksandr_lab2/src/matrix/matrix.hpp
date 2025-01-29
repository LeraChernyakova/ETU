#include <vector>
#include <cstdlib>
#include <fstream>

class Matrix {
public:
    std::vector<std::vector<int>> matrix;
    Matrix(int size);
    Matrix(std::vector<std::vector<int>> matrix);
    friend Matrix operator*(const Matrix &left, const Matrix &right);
    friend std::ofstream& operator<<(std::ofstream& out, Matrix& matrix);
};