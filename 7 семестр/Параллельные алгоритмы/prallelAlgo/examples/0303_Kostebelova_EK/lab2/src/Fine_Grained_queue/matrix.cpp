#include "matrix.h"


Matrix::Matrix(int MATRIX_SIZE) {
    this->matrix = std::vector(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE));
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            this->matrix[i][j] = -10 + rand() % 21;
        }
    }
}

Matrix::Matrix(std::vector<std::vector<int>> matrixInput) {
    int size = matrixInput.size();
    this->matrix = std::vector(size, std::vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            this->matrix[i][j] = matrixInput[i][j];
        }
    }
}

Matrix operator*(const Matrix &matrixA, const Matrix &matrixB) {
    int size = matrixA.matrix.size();
    auto resultMatrix = std::vector(size, std::vector<int>(size));
    int count;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            count = 0;
            for (int k = 0; k < size; k++) {
                count += (matrixA.matrix[i][k] * matrixB.matrix[k][j]);
            }
            resultMatrix[i][j] = count;
        }
    }
    return Matrix(resultMatrix);
}

std::ofstream& operator<<(std::ofstream& out, Matrix& matrixOutput) {
    for (int i = 0; i < matrixOutput.matrix.size(); i++) {
        for (int j = 0; j < matrixOutput.matrix[i].size(); j++) {
            out << matrixOutput.matrix[i][j] << " ";
        }
        out << std::endl;
    }
    out << std::endl;
    return out;
}
