#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include "Utils.hpp"
#include "Matrix.hpp"

using namespace std;

class Strassen {

private:
    static const int strassenLowerBound = 8;

public:
    static void defaultMatrixMultiplication(const Matrix &firstMatrix,
                                            const Matrix &secondMatrix,
                                            Matrix& resultMatrix
    ) {
#ifdef DEBUG
        firstMatrix.printMatrix();
        cout << '\n';
        secondMatrix.printMatrix();
#endif

        multiplicationStrassen(firstMatrix, secondMatrix, resultMatrix, 0);

#ifdef DEBUG
        resultMatrix.printMatrix();
        cout << "\n";
#endif
    }

private:
    static void multiplicationStrassen(const Matrix &firstMatrix,
                                       const Matrix &secondMatrix,
                                       Matrix& resultMatrix,
                                       int depthOfRecursion
            ) {
#ifdef DEBUG
        assert(0 == ((int)firstMatrix.rows() & ((int)firstMatrix.rows() - 1))); // проверка на степень матрицы
#endif

        int halfSize = (int)firstMatrix.rows() / 2;
        if (halfSize <= strassenLowerBound) { // если не нужно больше спускаться в рекурсию
#ifdef DEBUG
            log("start sync multiplication");
#endif
            multiplicationSync(firstMatrix, secondMatrix, resultMatrix);
            return;
        }

        Matrix a11 = firstMatrix.slice(halfSize, halfSize, 0, 0);
        Matrix a12 = firstMatrix.slice(halfSize, halfSize, 0, halfSize);
        Matrix a21 = firstMatrix.slice(halfSize, halfSize, halfSize, 0);
        Matrix a22 = firstMatrix.slice(halfSize, halfSize, halfSize, halfSize);

        Matrix b11 = secondMatrix.slice(halfSize, halfSize, 0, 0);
        Matrix b12 = secondMatrix.slice(halfSize, halfSize, 0, halfSize);
        Matrix b21 = secondMatrix.slice(halfSize, halfSize, halfSize, 0);
        Matrix b22 = secondMatrix.slice(halfSize, halfSize, halfSize, halfSize);

        Matrix d(halfSize, halfSize);
        Matrix d1(halfSize, halfSize);
        Matrix d2(halfSize, halfSize);
        Matrix h1(halfSize, halfSize);
        Matrix h2(halfSize, halfSize);
        Matrix v1(halfSize, halfSize);
        Matrix v2(halfSize, halfSize);

        if (depthOfRecursion == 0) {
            vector<thread> strassenThreads;
            strassenThreads.emplace_back(multiplicationStrassen, a11 + a22, b11 + b22, ref(d), depthOfRecursion + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a12 - a22, b21 + b22, ref(d1), depthOfRecursion + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a21 - a11, b11 + b12, ref(d2), depthOfRecursion + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a11 + a12, b22, ref(h1), depthOfRecursion + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a21 + a22, b11, ref(h2), depthOfRecursion + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a22, b21 - b11, ref(v1), depthOfRecursion + 1);
            strassenThreads.emplace_back(multiplicationStrassen, a11, b12 - b22, ref(v2), depthOfRecursion + 1);

            for (thread& thread : strassenThreads) {
                thread.join();
            }
        } else {
            multiplicationStrassen(a11 + a22, b11 + b22, d, depthOfRecursion + 1);
            multiplicationStrassen(a12 - a22, b21 + b22, d1, depthOfRecursion + 1);
            multiplicationStrassen(a21 - a11, b11 + b12, d2, depthOfRecursion + 1);
            multiplicationStrassen(a11 + a12, b22, h1, depthOfRecursion + 1);
            multiplicationStrassen(a21 + a22, b11, h2, depthOfRecursion + 1);
            multiplicationStrassen(a22, b21 - b11, v1, depthOfRecursion + 1);
            multiplicationStrassen(a11, b12 - b22, v2, depthOfRecursion + 1);
        }

        resultMatrix.insert(d + d1 + v1 - h1, 0, 0);
        resultMatrix.insert(v2 + h1, 0, halfSize);
        resultMatrix.insert(v1 + h2, halfSize, 0);
        resultMatrix.insert(d + d2 + v2 - h2, halfSize, halfSize);

    }

    static void multiplicationSync(const Matrix &firstMatrix,
                                   const Matrix &secondMatrix,
                                   Matrix& resultMatrix
            ) {
#ifdef DEBUG
        assert(firstMatrix.rows() == secondMatrix.rows());
        assert(firstMatrix.rows() == resultMatrix.rows());
#endif

        for (int i = 0; i < firstMatrix.rows(); ++i) {
            for (int j = 0; j < firstMatrix.columns(); ++j) {
                resultMatrix.data[i][j] = 0;
                for (int k = 0; k < firstMatrix.rows(); k++) {
                    resultMatrix.data[i][j] += firstMatrix.data[i][k] * secondMatrix.data[k][j];
                }
            }
        }
    }
};