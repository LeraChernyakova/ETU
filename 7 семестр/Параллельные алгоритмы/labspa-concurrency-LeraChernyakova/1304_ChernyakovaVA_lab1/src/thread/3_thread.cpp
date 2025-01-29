#include "../matrix/matrix.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>

Matrix leftMatrix, rightMatrix, resultMatrix;

void createMatrices(int rowsLeft, int colsLeft, int rowsRight, int colsRight) {
    leftMatrix = createMatrix(rowsLeft, colsLeft);
    printMatrix(leftMatrix, "left_matrix");
    rightMatrix = createMatrix(rowsRight, colsRight);
    printMatrix(rightMatrix, "right_matrix");
}

void multiplicationMatrices() {
    resultMatrix = leftMatrix * rightMatrix;
}

void outputMatrix() {
    printMatrix(resultMatrix, "result_matrix");
}

int main(int argc, char* argv[]) {
    try {
        int leftRows, leftCols, rightRows, rightCols;
        if (!readRowsCols(argc, argv, leftRows, leftCols, rightRows, rightCols)) {
            throw std::runtime_error("Write: " + std::string(argv[0])
                    + " left_matrix_rows left_matrix_cols right_matrix_rows right_matrix_cols ");
        }
        if (leftCols != rightRows) {
            throw std::invalid_argument("Error: Matrix dimensions do not match for multiplication");
        }

        std::srand(static_cast<unsigned>(std::time(nullptr)));
        std::thread readerThread(createMatrices, leftRows, leftCols, rightRows, rightCols);
        readerThread.join();

        std::thread mainThread(multiplicationMatrices);
        mainThread.join();

        std::thread writerThread(outputMatrix);
        writerThread.join();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
