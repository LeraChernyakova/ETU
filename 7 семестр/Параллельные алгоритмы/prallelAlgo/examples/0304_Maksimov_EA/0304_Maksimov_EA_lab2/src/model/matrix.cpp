#include "matrix.h"

Matrix getTransposedMatrix(Matrix matrix) {
    Matrix transposedMatrix;
    int rows = matrix.size(), columns = matrix[0].size();

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

Matrix squareMatrix(Matrix A) {
    std::vector<Matrix> matricesToMultiply = {A, A};
    multiplyMatrices(&matricesToMultiply);
    return matricesToMultiply[2];
}

Matrix generateMatrix() {
    int rows = MATRIX_SIZE;
    Matrix matrix = Matrix(rows, std::vector<int>(rows, 0));
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < rows; j++) {
            matrix[i][j] = rand() % MATRIX_MAX_VALUE;
        }
    }

    return matrix;
}
