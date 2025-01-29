#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "./matrix.h"
#include "./common.h"

Matrix m1, m2, resultMatrix;

void createGlobalMatrix(int rows1, int cols1, int rows2, int cols2) {
    m1 = createMatrix(rows1, cols1);
    m2 = createMatrix(rows2, cols2);
}

void execute() {
    resultMatrix = m1 * m2;
}

void writeAnswer() {
    printMatrix(resultMatrix);
}

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));
    int rows1, cols1, rows2, cols2;
    if (!readMatrices(argc, argv, rows1, cols1, rows2, cols2))
    {
        std::cout << "Usage: " << argv[0] << " m1_rows m1_cols m2_rows m2_cols\n";
        return 1;
    }
    if (cols1 != rows2) {
        std::cout << "Wrong matrix sizes\n";
        return 1;
    }

    std::thread reader(createGlobalMatrix, rows1, cols1, rows2, cols2);
    reader.join();
    std::thread executor(execute);
    executor.join();
    std::thread writer(writeAnswer);
    writer.join();

    return 0;
}