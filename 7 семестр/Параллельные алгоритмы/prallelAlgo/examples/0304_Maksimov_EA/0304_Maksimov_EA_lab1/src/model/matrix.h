#pragma once

#include <vector>
#include <iostream>

using Matrix = std::vector<std::vector<int>>;

Matrix getTransposedMatrix(Matrix matrix);
void multiplyMatrices(std::vector<Matrix>* matricesPointer);
void multiplyMatricesMultithread(std::vector<Matrix>* matricesPointer, int indexFirst, int indexLast);
std::vector<int> serializeManyMatrices(std::vector<Matrix> matrices);
std::vector<Matrix> deserializeManyMatrices(std::vector<int> buffer);
