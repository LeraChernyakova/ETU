//
// Created by mikeasta on 11/20/23.
//

#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include "Matrix.h"

#define THREADS_AMOUNT 10

class DefaultMultiplier {
private:
    static void multiplyMatricesInThread(
            const Matrix& leftMatrix,
            const Matrix& rightMatrix,
            Matrix& resultMatrix,
            int startItem,
            int itemsAmount
            ) {
        int matrixSize = leftMatrix.rows();
        int currentItem = startItem;
        int matrixItemsAmount = matrixSize * matrixSize;
        while (currentItem < matrixItemsAmount && currentItem - startItem < itemsAmount) {
            int i = currentItem / matrixSize;
            int j = currentItem % matrixSize;
            resultMatrix.data[i][j] = 0;
            for (size_t k = 0; k < matrixSize; k++)
                resultMatrix.data[i][j] += leftMatrix.data[i][k] * rightMatrix.data[k][j];
            currentItem++;
        }
    }

public:
    static void defaultMatrixMultiplication(
            const Matrix& leftMatrix,
            const Matrix& rightMatrix,
            Matrix& resultMatrix
            ) {
        std::vector<std::thread> matrixMultipliers;
        matrixMultipliers.reserve(THREADS_AMOUNT);

        int matrixSize = leftMatrix.rows();
        int itemsAmount = matrixSize * matrixSize;
        int itemsPerThread = itemsAmount / THREADS_AMOUNT + (itemsAmount % THREADS_AMOUNT != 0);

        for (size_t i = 0; i < THREADS_AMOUNT; i++) {
            int itemsToMultiply = i == THREADS_AMOUNT - 1 ? itemsAmount - (THREADS_AMOUNT - 1) * itemsPerThread: itemsPerThread;
            matrixMultipliers.emplace_back(
                    multiplyMatricesInThread,
                    std::ref(leftMatrix),
                    std::ref(rightMatrix),
                    std::ref(resultMatrix),
                    i*itemsPerThread,
                    itemsToMultiply
                    );
        }

        for (auto& thread: matrixMultipliers)
            thread.join();
    }


};
