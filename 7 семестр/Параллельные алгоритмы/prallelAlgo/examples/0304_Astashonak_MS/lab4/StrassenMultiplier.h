//
// Created by mikeasta on 11/20/23.
//

#pragma once

#include <iostream>
#include "Matrix.h"

class StrassenMultiplier {
private:
    static const int lowerBound = 8;

    static void multiplicationSync(
            const Matrix& leftMatrix,
            const Matrix& rightMatrix,
            Matrix& resultMatrix
            ) {
        int matrixSize = leftMatrix.rows();
        for (size_t i = 0; i < matrixSize; i++) {
            for (size_t j = 0; j < matrixSize; j++) {
                resultMatrix.data[i][j] = 0;
                for (size_t k = 0; k < matrixSize; k++)
                    resultMatrix.data[i][j] += leftMatrix.data[i][k] * rightMatrix.data[k][j];
            }
        }
    }

    static void multiplicationStrassen(
            const Matrix& leftMatrix,
            const Matrix& rightMatrix,
            Matrix& resultMatrix,
            int depth
            ) {
        int halfSize = (int)leftMatrix.rows() / 2;
        if (halfSize <= lowerBound) {
            multiplicationSync(leftMatrix, rightMatrix, resultMatrix);
            return;
        }

        Matrix a11 = leftMatrix.slice(halfSize, halfSize, 0, 0);
        Matrix a12 = leftMatrix.slice(halfSize, halfSize, 0, halfSize);
        Matrix a21 = leftMatrix.slice(halfSize, halfSize, halfSize, 0);
        Matrix a22 = leftMatrix.slice(halfSize, halfSize, halfSize, halfSize);

        Matrix b11 = rightMatrix.slice(halfSize, halfSize, 0, 0);
        Matrix b12 = rightMatrix.slice(halfSize, halfSize, 0, halfSize);
        Matrix b21 = rightMatrix.slice(halfSize, halfSize, halfSize, 0);
        Matrix b22 = rightMatrix.slice(halfSize, halfSize, halfSize, halfSize);

        Matrix d(halfSize, halfSize);
        Matrix d1(halfSize, halfSize);
        Matrix d2(halfSize, halfSize);
        Matrix h1(halfSize, halfSize);
        Matrix h2(halfSize, halfSize);
        Matrix v1(halfSize, halfSize);
        Matrix v2(halfSize, halfSize);

        if (depth == 0) {
            std::vector<std::thread> strassenThreads;
            strassenThreads.emplace_back(multiplicationStrassen, a11 + a22, b11 + b22, std::ref(d), depth + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a12 - a22, b21 + b22, std::ref(d1), depth + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a21 - a11, b11 + b12, std::ref(d2), depth + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a11 + a12, b22, std::ref(h1), depth + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a21 + a22, b11, std::ref(h2), depth + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a22, b21 - b11, std::ref(v1), depth + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a11, b12 - b22, std::ref(v2), depth + 1);

            for (std::thread& thread : strassenThreads)
                thread.join();

        } else {
            multiplicationStrassen(a11 + a22, b11 + b22, d, depth + 1);
            multiplicationStrassen(a12 - a22, b21 + b22, d1, depth + 1);
            multiplicationStrassen(a21 - a11, b11 + b12, d2, depth + 1);
            multiplicationStrassen(a11 + a12, b22, h1, depth + 1);
            multiplicationStrassen(a21 + a22, b11, h2, depth + 1);
            multiplicationStrassen(a22, b21 - b11, v1, depth + 1);
            multiplicationStrassen(a11, b12 - b22, v2, depth + 1);
        }

        resultMatrix.insert(d + d1 + v1 - h1, 0, 0);
        resultMatrix.insert(v2 + h1, 0, halfSize);
        resultMatrix.insert(v1 + h2, halfSize, 0);
        resultMatrix.insert(d + d2 + v2 - h2, halfSize, halfSize);
    }

public:
    static void defaultMatrixMultiplication(
            const Matrix& leftMatrix,
            const Matrix& rightMatrix,
            Matrix& resultMatrix
            ) {
        multiplicationStrassen(leftMatrix, rightMatrix, resultMatrix, 0);
    }
};
