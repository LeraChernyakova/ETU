#include <thread>
#include <chrono>

#include "../io/input.h"
#include "../io/output.h"
#include "../io/files.h"

// ================================

void readMatrices(std::vector<Matrix>* matricesPointer) {
    readMatricesFromFile(INPUT_THREADS_FILE, matricesPointer);
    std::cout << "Process: read matrices.\n";
    return;
}

void calculate(std::vector<Matrix>* matricesPointer) {
    std::cout << "Process: calculate.\n";
    auto timestampStart = std::chrono::high_resolution_clock::now();
    multiplyMatrices(matricesPointer);
    auto timestampFinish = std::chrono::high_resolution_clock::now();
    auto timeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timestampFinish-timestampStart);
    std::cout << "Time passed: " << timeDuration.count() << "ms.\n";
    return;
}

void writeMatrix(std::vector<Matrix>* matricesPointer) {
    writeMatrixToFile(OUTPUT_FILE, (*matricesPointer)[2]);
    std::cout << "Process: write matrix.\n";
    return;
}

// ================================

int main() {
    std::vector<Matrix> matrices;

    std::thread threadReadMatrices(readMatrices, &matrices);
    threadReadMatrices.join();
    std::thread threadCalculate(calculate, &matrices);
    threadCalculate.join();
    std::thread threadWriteMatrix(writeMatrix, &matrices);
    threadWriteMatrix.join();

    std::cout << "\nSee answer in ./data/output.txt file.\n\n";
    return 0;
}
