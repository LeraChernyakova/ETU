#include <chrono>

#include "strassen.h"
#include "../io/input.h"
#include "../io/output.h"
#include "../model/matrix.h"

int main() {
    std::vector<int> inputValues = readInputFile();
    if(inputValues.size() != 1) {
        return -1;
    }
    int N = inputValues[0];

    // ==== Получение матриц ====

    std::vector<Matrix> matrices;
    for(int i = 0; i < 2; i++) {
        matrices.push_back(generateMatrix(N));
    }

    // ==== Подсчёт ====
    
    auto timestampStart = std::chrono::high_resolution_clock::now();
    multiplyStrassen(&matrices, N);
    auto timestampFinish = std::chrono::high_resolution_clock::now();
    auto timeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timestampFinish-timestampStart);
    std::cout << "Strassen, matrix size: " << N << ", time passed: " << timeDuration.count() << "ms.\n";

    // ==== Запись ====

    if(!openOutputFile()) {
        return -1;
    }

    writeMatrixToFile(matrices[2]);
    closeOutputFile();

    return 0;
}
