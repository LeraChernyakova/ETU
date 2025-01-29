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

// При вызове этой функции нужно подготовить объектs. 
// 1. Матрица B должна быть транспонирована.
// 2. В matricesPointer по индексу 2 уже лежит пустая матрица.
void multiplyMatricesMultithread(std::vector<Matrix>* matricesPointer, int indexFirst, int indexLast) {
    Matrix A = (*matricesPointer)[0];
    Matrix B = (*matricesPointer)[1];
    int rowsB = B.size();
    for(int i = indexFirst; i < indexLast; i++) {
        (*matricesPointer)[2][i/rowsB][i%rowsB] = multiplyVectors(A[i/rowsB], B[i%rowsB]);
    }

    return;
}

std::vector<int> serializeManyMatrices(std::vector<Matrix> matrices) {
    int matricesAmount = matrices.size();
    std::vector<int> buffer;
    buffer.push_back(matricesAmount);

    for(int counter = 0; counter < matricesAmount; counter++) {
        int rows = matrices[counter].size(), columns = matrices[counter][0].size();
        buffer.push_back(rows);
        buffer.push_back(columns);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                buffer.push_back(matrices[counter][i][j]);
            }
        }
    }

    return buffer;
}

std::vector<Matrix> deserializeManyMatrices(std::vector<int> buffer) {
    std::vector<Matrix> matrices;
    int matricesAmount = buffer[0];
    int bufferCounter = 1;
    if((matricesAmount < 1) || (matricesAmount > 2))
        return matrices;

    for(int counter = 0; counter < matricesAmount; counter++) {
        Matrix matrix;
        int rows = buffer[bufferCounter], columns = buffer[bufferCounter+1];
        bufferCounter += 2;
        if((rows <= 0) || (columns <= 0) || (rows > 1<<10) || (columns > 1<<10)) {
            matrices.push_back(matrix);
            continue;
        }

        for(int i = 0; i < rows; i++) {
            std::vector<int> row;
            for(int j = 0; j < columns; j++) {
                row.push_back(buffer[bufferCounter]);
                bufferCounter++;
            }
            matrix.push_back(row);
        }
        matrices.push_back(matrix);
    }
    
    return matrices;
}
