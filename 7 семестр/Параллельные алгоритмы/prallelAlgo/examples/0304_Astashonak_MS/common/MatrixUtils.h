//
// Created by mikeasta on 10/22/23.
//
#pragma once
#define MATRIX_SIZE 300
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

namespace MatrixUtils {
    // Filling matrix with random values
    void generateMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int min = 0, int max = 10) {
        for (size_t row = 0; row < MATRIX_SIZE; row++) {
            for (size_t col = 0; col < MATRIX_SIZE; col++) {
                matrix[row][col] = rand() % (max - min + 1) + min ;
            }
        }
    }

    // Logging matrix
    void logMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
        for (size_t row = 0; row < MATRIX_SIZE; row++) {
            for (size_t col = 0; col < MATRIX_SIZE; col++) {
                std::cout << matrix[row][col] << " ";
            }
            std::cout << std::endl;
        }
    }


    // Matrices multiplication
    void multiplyMatrices (
            int leftMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int rightMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int resultMatrix[MATRIX_SIZE][MATRIX_SIZE]
        ) {
        for (size_t row = 0; row < MATRIX_SIZE; row++) {
            for (size_t col = 0; col < MATRIX_SIZE; col++) {
                resultMatrix[row][col] = 0;
                for (size_t k = 0; k < MATRIX_SIZE; k++) {
                    resultMatrix[row][col] += leftMatrix[row][k] * rightMatrix[k][col];
                }
            }
        }
    }

    // Matrices multiplication in parts
    void multiplyMatricesUsingThreads (
            int leftMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int rightMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int resultMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int startItemIndex,
            int itemsToMultiplyAmount
        ) {
        int currentItemIndex = startItemIndex;
        int matrixItemsAmount = MATRIX_SIZE * MATRIX_SIZE;
        while (currentItemIndex < matrixItemsAmount && (currentItemIndex - startItemIndex) < itemsToMultiplyAmount) {
            int row = currentItemIndex / MATRIX_SIZE;
            int col = currentItemIndex % MATRIX_SIZE;
            resultMatrix[row][col] = 0;
            for (size_t k = 0; k < MATRIX_SIZE; k++) {
                resultMatrix[row][col] += leftMatrix[row][k] * rightMatrix[k][col];
            }
            currentItemIndex++;
        }
    }

    // Multiply only one matrix cell
    void multiplyMatricesCell(
            int row,
            int col,
            int leftMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int rightMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int resultMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
        resultMatrix[row][col] = 0;
        for (size_t k = 0; k < MATRIX_SIZE; k++) {
            resultMatrix[row][col] += leftMatrix[row][k] * rightMatrix[k][col];
        }
    }
}

// Message logging
void log(const std::string& message) {
    std::cout << message << std::endl;
}