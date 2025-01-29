#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "./matrix.h"
#include "./common.h"
#include <vector>

Matrix m1, m2, resultMatrix;

void multiplyMatrix(int pCount, int curIndex){
    for (int r = 0; r < resultMatrix.getRows(); r++) {
        for (int c = 0; c < resultMatrix.getCols(); c++) {
            for (int i = 0; i < m1.getCols(); i++) {
                if ((r + c) % pCount == curIndex) {
                    resultMatrix.getElem(r, c) += m1.getElem(r, i) * m2.getElem(i, c);
                }
            }
        }
    }
}

void createGlobalMatrix(int rows1, int cols1, int rows2, int cols2) {
    m1 = createMatrix(rows1, cols1);
    m2 = createMatrix(rows2, cols2);
}

void execute(int p) {
    resultMatrix = Matrix(m1.getRows(), m2.getCols());
    std::vector<std::thread> threads;
    threads.reserve(p);
    for (int i = 0; i < p; i++) {
        threads.emplace_back(multiplyMatrix, p, i);
    }
    for (int i = 0; i < p; i++) {
        threads[i].join();
    }
}

void writeAnswer() {
    printMatrix(resultMatrix);
}

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));
    int rows1, cols1, rows2, cols2, p;
    if (argc != 6 || !readMatrices(argc, argv, rows1, cols1, rows2, cols2) || !readInt(argv[5], p))
    {
        std::cout << "Usage: " << argv[0] << " m1_rows m1_cols m2_rows m2_cols p\n";
        return 1;
    }
    if (cols1 != rows2) {
        std::cout << "Wrong matrix sizes\n";
        return 1;
    }
    std::thread reader(createGlobalMatrix, rows1, cols1, rows2, cols2);
    reader.join();
    std::thread executor(execute, p);
    executor.join();
    std::thread writer(writeAnswer);
    writer.join();

    return 0;
}