#pragma once

#define MATRIX_SIZE 400
#define FIRST_MATRIX_FILE "./resources/firstMatrix.txt"
#define SECOND_MATRIX_FILE "./resources/secondMatrix.txt"
#define RESULT_MATRIX_FILE "./resources/resultMatrix.txt"

#include <string>
#include <fstream>
#include <iostream>

namespace MatrixUtils {

    void fillMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                matrix[i][j] = rand() % 50;
            }
        }
    }

    void writeToFile(int matrix[MATRIX_SIZE][MATRIX_SIZE], const std::string &filename) {
        std::ofstream outFile;
        outFile.open(filename);

        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                outFile << matrix[i][j] << " ";
            }
            outFile << '\n';
        }

        outFile.close();
    }

    void readFromFile(int matrix[MATRIX_SIZE][MATRIX_SIZE], const std::string &filename) {
        std::ifstream inFile;
        inFile.open(filename);

        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                inFile >> matrix[i][j];
            }
        }

        inFile.close();
    }

    void multiplyMatrices(int firstMatrix[MATRIX_SIZE][MATRIX_SIZE],
                          int secondMatrix[MATRIX_SIZE][MATRIX_SIZE],
                          int resultMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                resultMatrix[i][j] = 0;
                for (int k = 0; k < MATRIX_SIZE; k++) {
                    resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
                }
            }
        }
    }

    void multiplyMatricesInThread(int firstMatrix[MATRIX_SIZE][MATRIX_SIZE],
                                  int secondMatrix[MATRIX_SIZE][MATRIX_SIZE],
                                  int resultMatrix[MATRIX_SIZE][MATRIX_SIZE],
                                  int startItem,
                                  int itemsAmount) {
        int currentItem = startItem;
        int matrixItemsAmount = MATRIX_SIZE * MATRIX_SIZE;
        while (currentItem < matrixItemsAmount && currentItem - startItem < itemsAmount) {
            int i = currentItem / MATRIX_SIZE;
            int j = currentItem % MATRIX_SIZE;
            resultMatrix[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
            currentItem++;
        }
    }
}

void log(const std::string& message) {
    std::cout << message << '\n';
}
