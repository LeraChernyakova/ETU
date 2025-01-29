#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<uint>>;


void printMatrix(Matrix &matrix);
Matrix generateMatrix(size_t size);
void multiplyVectorMatrixRow(std::size_t i,
                             std::size_t j,
                             Matrix &matr1,
                             Matrix &matr2,
                             Matrix &result);

Matrix multiplyMatrix(Matrix &matrix1, Matrix &matrix2);
Matrix addMatrix(Matrix &m1, Matrix &m2);
Matrix subMatrix(Matrix &m1, Matrix &m2);
Matrix slice(Matrix &matrix,
             std::size_t piece,
             std::size_t startRow,
             std::size_t startCol);
void insert(Matrix& matrix,
              Matrix& matrixToInsert,
              std::size_t startRow,
              std::size_t startCol);             

inline Matrix operator+(Matrix &m1, Matrix &m2)
{
    return addMatrix(m1, m2);
}

inline Matrix operator-(Matrix &m1, Matrix &m2)
{
    return subMatrix(m1, m2);
}

#endif //MATRIX_FUNCTIONS_H