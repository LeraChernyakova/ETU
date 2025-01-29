//
// Created by mikeasta on 10/28/23.
//
#pragma once
#include "MatrixUtils.h"

namespace SharedMemoryUtils {
    // Saves data about one matrix
    void saveMatrix(
            int matrix[MATRIX_SIZE][MATRIX_SIZE],
            int* sharedMemory,
            int offset = 0) {
        for (size_t row = 0; row < MATRIX_SIZE; row++) {
            for (size_t col = 0; col < MATRIX_SIZE; col++) {
                sharedMemory[offset + row * MATRIX_SIZE + col] = matrix[row][col];
            }
        }
    }

    // Gets matrix from shared memory
    void getMatrix(
            int matrix[MATRIX_SIZE][MATRIX_SIZE],
            int* sharedMemory,
            int offset = 0) {
        for (size_t row = 0; row < MATRIX_SIZE; row++) {
            for (size_t col = 0; col < MATRIX_SIZE; col++) {
                matrix[row][col] = sharedMemory[offset + row * MATRIX_SIZE + col];
            }
        }
    }

    // Save data about two matrices in shared memory
    void saveTwoMatrices(
            int leftMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int rightMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int* sharedMemory) {
        // Saves left matrix
        for (size_t row = 0; row < MATRIX_SIZE; row++) {
            for (size_t col = 0; col < MATRIX_SIZE; col++) {
                sharedMemory[row * MATRIX_SIZE + col] = leftMatrix[row][col];
            }
        }

        // Saves right matrix
        int offset = MATRIX_SIZE * MATRIX_SIZE;
        for (size_t row = 0; row < MATRIX_SIZE; row++) {
            for (size_t col = 0; col < MATRIX_SIZE; col++) {
                sharedMemory[offset + row * MATRIX_SIZE + col] = rightMatrix[row][col];
            }
        }
    }

    // Get two matrices from shared memory
    void getTwoMatrices(
            int leftMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int rightMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int* sharedMemory) {
        // Gets left matrix
        for (size_t row = 0; row < MATRIX_SIZE; row++) {
            for (size_t col = 0; col < MATRIX_SIZE; col++) {
                leftMatrix[row][col] = sharedMemory[row * MATRIX_SIZE + col];
            }
        }

        // Gets right matrix
        int offset = MATRIX_SIZE * MATRIX_SIZE;
        for (size_t row = 0; row < MATRIX_SIZE; row++) {
            for (size_t col = 0; col < MATRIX_SIZE; col++) {
                rightMatrix[row][col] = sharedMemory[offset + row * MATRIX_SIZE + col];
            }
        }
    }
}