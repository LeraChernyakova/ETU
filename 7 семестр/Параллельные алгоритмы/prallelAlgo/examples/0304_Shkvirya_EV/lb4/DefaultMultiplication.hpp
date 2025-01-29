#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include "Utils.hpp"
#include "Matrix.hpp"

using namespace std;

class DefaultMultiplication {
public:
    static void defaultMatrixMultiplication(const Matrix &firstMatrix,
                                     const Matrix &secondMatrix,
                                     Matrix &resultMatrix
    ) {
        int threadAmount = 7;
        vector<thread> matricesMultiplier;
        matricesMultiplier.reserve(threadAmount);

#ifdef DEBUG
        firstMatrix.printMatrix();
        secondMatrix.printMatrix();
#endif

        int matrixSize = firstMatrix.rows();
        int itemsAmount = matrixSize * matrixSize;
        int itemsPerThread = itemsAmount / threadAmount + (itemsAmount % threadAmount != 0);
        for (int i = 0; i < threadAmount; i++) {
            matricesMultiplier.emplace_back(multiplyMatricesInThread,
                                            std::ref(firstMatrix),
                                            std::ref(secondMatrix),
                                            std::ref(resultMatrix),
                                            i * itemsPerThread,
                                            (i == threadAmount - 1 ? itemsAmount - (threadAmount - 1) * itemsPerThread
                                                                   : itemsPerThread));
        }

        for (auto &thread: matricesMultiplier) {
            thread.join();
        }

#ifdef DEBUG
        resultMatrix.printMatrix();
        cout << "\n";
#endif
    }

private:
    static void multiplyMatricesInThread(const Matrix &firstMatrix,
                                  const Matrix &secondMatrix,
                                  Matrix &resultMatrix,
                                  int startItem,
                                  int itemsAmount) {
        int size = firstMatrix.rows();
        int currentItem = startItem;
        int matrixItemsAmount = size * size;
        while (currentItem < matrixItemsAmount && currentItem - startItem < itemsAmount) {
            int i = currentItem / size;
            int j = currentItem % size;
            resultMatrix.data[i][j] = 0;
            for (int k = 0; k < size; k++) {
                resultMatrix.data[i][j] += firstMatrix.data[i][k] * secondMatrix.data[k][j];
            }
            currentItem++;
        }
    }
};

