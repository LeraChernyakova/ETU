#include "matrix.h"
#include <thread>

Matrix getTransposedMatrix(Matrix matrix) {
    int rows = matrix.size(), columns = matrix[0].size();
    Matrix transposedMatrix;

    for(int j = 0; j < columns; j++) {
        std::vector<int> row;
        for(int i = 0; i < rows; i++) {
            row.push_back(matrix[i][j]);
        }
        transposedMatrix.push_back(row);
    }

    return transposedMatrix;
}

int multiplyVectors(std::vector<int> a, std::vector<int> b) {
    int columns = a.size();
    int result = 0;

    for(int i = 0; i < columns; i++) {
        result += a[i]*b[i];
    }

    return result;
}

void multiplyMatrices(std::vector<Matrix>* matricesPointer) {
    Matrix A = (*matricesPointer)[0];
    Matrix B = getTransposedMatrix((*matricesPointer)[1]);
    int rowsA = A.size();
    int rowsB = B.size();
    (*matricesPointer).push_back(Matrix(rowsA, std::vector<int>(rowsB, 0)));

    for(int i = 0; i < rowsA; i++) {
        for(int j = 0; j < rowsB; j++) {
            (*matricesPointer)[2][i][j] = multiplyVectors(A[i], B[j]);
        }
    }

    return;
}

Matrix generateMatrix(int rows) {
    Matrix matrix = Matrix(rows, std::vector<int>(rows, 0));
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < rows; j++) {
            matrix[i][j] = rand() % MATRIX_MAX_VALUE;
        }
    }

    return matrix;
}

void printMatrix(Matrix A) {
    int size = A.size();
    for(int i = 0; i < size; i++) {
        std::cout << std::endl;
        for(int j = 0; j < size; j++) {
            std::cout << A[i][j] << " ";
        }
    }
    std::cout << std::endl;
}

Matrix operator+(Matrix A, Matrix B) {
    int size = A.size();
    Matrix C = Matrix(size, std::vector<int>(size, 0));

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

Matrix operator-(Matrix A, Matrix B) {
    int size = A.size();
    Matrix C = Matrix(size, std::vector<int>(size, 0));

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}
