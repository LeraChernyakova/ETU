#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<long long int>>;

void printMatrix(Matrix &matrix);
Matrix generateMatrix(size_t size);
void multiplyVectorMatrixRow(std::size_t i,
                             std::size_t j,
                             Matrix &matr1,
                             Matrix &matr2,
                             Matrix &result);