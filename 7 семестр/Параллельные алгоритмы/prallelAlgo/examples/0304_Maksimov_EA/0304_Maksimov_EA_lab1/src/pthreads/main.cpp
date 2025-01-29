#include <thread>
#include <chrono>

#include "../io/input.h"
#include "../io/output.h"
#include "../io/files.h"
#include "../model/matrix.h"

#define P 20
#define P_MAX 256

// ================================

void readMatrices(std::vector<Matrix>* matricesPointer) {
    readMatricesFromFile(INPUT_THREADS_FILE, matricesPointer);
    std::cout << "Thread: read matrices.\n";
    return;
}

void writeMatrix(std::vector<Matrix>* matricesPointer) {
    writeMatrixToFile(OUTPUT_FILE, (*matricesPointer)[2]);
    std::cout << "Thread: write matrix.\n";
    return;
}

// ================================

int main() {
    std::vector<Matrix> matrices;
    int threadsAmount = P;
    if((threadsAmount < 1) || (threadsAmount > P_MAX)) {
        threadsAmount = 1;
    }

    // ==== Чтение ====

    std::thread threadReadMatrices(readMatrices, &matrices);
    threadReadMatrices.join();

    // ==== Подсчёт ====

    std::vector<std::thread> threads;
    // Подготовка к выполнению.
    // 1. Транспонируем матрицу B.
    matrices[1] = getTransposedMatrix(matrices[1]);
    int rows = matrices[0].size(), columns = matrices[1][0].size();
    // 2. Создаём пустую матрицу.
    matrices.push_back(Matrix(rows, std::vector<int>(columns, 0)));
    int threadChunkSize = rows*columns/threadsAmount;
    auto timestampStart = std::chrono::high_resolution_clock::now();
    // Добавляем в список потоков все, кроме последнего.
    for(int i = 0; i < threadsAmount-1; i++) {
        threads.push_back(std::thread(multiplyMatricesMultithread, &matrices, i*threadChunkSize, (i+1)*threadChunkSize));
    }
    // В последний поток дополнительно закидываем лишнее.
    threads.push_back(std::thread(multiplyMatricesMultithread, &matrices, (threadsAmount-1)*threadChunkSize, rows*columns));
    for(int i = 0; i < threadsAmount; i++) {
        threads[i].join();
    }
    auto timestampFinish = std::chrono::high_resolution_clock::now();
    auto timeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timestampFinish-timestampStart);
    std::cout << "Threads: " << threadsAmount << ", time passed: " << timeDuration.count() << "ms.\n";

    // ==== Запись ====

    std::thread threadWriteMatrix(writeMatrix, &matrices);
    threadWriteMatrix.join();

    // ========

    return 0;
}
