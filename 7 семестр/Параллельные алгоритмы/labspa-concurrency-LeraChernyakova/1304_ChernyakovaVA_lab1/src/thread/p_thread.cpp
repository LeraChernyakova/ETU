#include "../matrix/matrix.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>

Matrix leftMatrix, rightMatrix, resultMatrix;

void createMatrices(int rowsLeft, int colsLeft, int rowsRight, int colsRight) {
    leftMatrix = createMatrix(rowsLeft, colsLeft);
    printMatrix(leftMatrix, "left_matrix");
    rightMatrix = createMatrix(rowsRight, colsRight);
    printMatrix(rightMatrix, "right_matrix");
}

void parallelMultiplication(int startRow, int endRow) {
    for (int row = startRow; row < endRow; row++) {
        for (int col = 0; col < resultMatrix.cols_; col++) {
            int sum = 0;
            for (int i = 0; i < leftMatrix.cols_; i++) {
                sum += leftMatrix.data_[row * leftMatrix.cols_ + i] * rightMatrix.data_[i * rightMatrix.cols_ + col];
            }
            resultMatrix.data_[row * resultMatrix.cols_ + col] = sum;
        }
    }
}

void multiplicationMatrices(int threadCount) {
    resultMatrix = Matrix(leftMatrix.rows_, rightMatrix.cols_);
    std::vector<std::thread> threads;
    threads.reserve(threadCount);

    int rowsPerThread, remainingRows;

    if (resultMatrix.rows_ < threadCount) {
        rowsPerThread = 1;
        remainingRows = 0;
    } else {
        rowsPerThread = resultMatrix.rows_ / threadCount;
        remainingRows = resultMatrix.rows_ % threadCount;
    }

    int startRow = 0;
    for (int i = 0; i < (resultMatrix.rows_ < threadCount ? resultMatrix.rows_ : threadCount); i++) {
        int endRow = startRow + rowsPerThread + (i < remainingRows ? 1 : 0);
        threads.emplace_back(parallelMultiplication, startRow, endRow);
        startRow = endRow;
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

void outputMatrix() {
    printMatrix(resultMatrix, "result_matrix");
}

int main(int argc, char* argv[]) {
    try {
        int leftRows, leftCols, rightRows, rightCols, threadCnt;
        if (!isNumber(argv[5], threadCnt) || !readRowsCols(argc, argv, leftRows, leftCols, rightRows, rightCols)
            || argc != 6) {
            throw std::runtime_error("Write: " + std::string(argv[0])
                    + " left_matrix_rows left_matrix_cols right_matrix_rows right_matrix_cols thread_count\n");
        }
        if (leftCols != rightRows) {
            throw std::invalid_argument("Error: Matrix dimensions do not match for multiplication\n");
        }

        std::srand(static_cast<unsigned>(std::time(nullptr)));
        std::thread readerThread(createMatrices, leftRows, leftCols, rightRows, rightCols);
        readerThread.join();

        std::thread mainThread(multiplicationMatrices, threadCnt);
        mainThread.join();

        std::thread writerThread(outputMatrix);
        writerThread.join();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}