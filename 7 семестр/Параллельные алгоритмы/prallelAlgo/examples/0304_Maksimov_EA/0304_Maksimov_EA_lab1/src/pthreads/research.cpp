#include <thread>
#include <chrono>

#include "../io/input.h"
#include "../io/output.h"
#include "../io/files.h"
#include "../model/matrix.h"

// ================================

void readMatrices(std::vector<Matrix>* matricesPointer) {
    readMatricesFromFile(INPUT_THREADS_FILE, matricesPointer);
    return;
}

void writeMatrix(std::vector<Matrix>* matricesPointer) {
    writeMatrixToFile(OUTPUT_FILE, (*matricesPointer)[2]);
    return;
}

// ================================

void pthreadRoutine(int threadsAmount, std::vector<Matrix>* matricesPointer, std::ofstream* outputFile) {
    std::vector<std::thread> threads;
    int rows = (*matricesPointer)[0].size(), columns = (*matricesPointer)[1][0].size();
    int threadChunkSize = rows*columns/threadsAmount;
    auto timestampStart = std::chrono::high_resolution_clock::now();
    // Все, кроме последнего.
    for(int i = 0; i < threadsAmount-1; i++) {
        threads.push_back(std::thread(multiplyMatricesMultithread, matricesPointer, i*threadChunkSize, (i+1)*threadChunkSize));
    }
    // Последний - в него закинем лишнее.
    threads.push_back(std::thread(multiplyMatricesMultithread, matricesPointer, (threadsAmount-1)*threadChunkSize, rows*columns));
    for(int i = 0; i < threadsAmount; i++) {
        threads[i].join();
    }
    auto timestampFinish = std::chrono::high_resolution_clock::now();
    auto timeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timestampFinish-timestampStart);
    std::cout << threadsAmount << " " << timeDuration.count() << std::endl;
    (*outputFile) << threadsAmount << " " << timeDuration.count() << std::endl;

    // ========

    return;
}

int main() {
    std::vector<Matrix> matrices;

    // ==== Открыть файл на запись ====

    std::ofstream fout(OUTPUT_FILE);
    if(!fout) {
        std::cout << "Cannot open file " << OUTPUT_FILE << " to write result.";
        return -1;
    }

    // ==== Чтение ====

    std::thread threadReadMatrices(readMatrices, &matrices);
    threadReadMatrices.join();

    // Подготовка к выполнению.
    // 1. Транспонируем матрицу B.
    matrices[1] = getTransposedMatrix(matrices[1]);
    int rows = matrices[0].size(), columns = matrices[1][0].size();
 
    // ==== Подсчёт ====

    int lastThreadAmount = 1;
    for(int i = 2; i < 10000; i++) {
        if(float(i)/float(lastThreadAmount) >= 1.1) {
            // 2. Создаём пустую матрицу.
            matrices.push_back(Matrix(rows, std::vector<int>(columns, 0)));
            // 3. Вызов функции.
            pthreadRoutine(lastThreadAmount, &matrices, &fout);
            lastThreadAmount = i;
            // 4. Удаляем заполненную старую матрицу.
            matrices.pop_back();
        }
    }

    matrices.push_back(Matrix(rows, std::vector<int>(columns, 0)));
    pthreadRoutine(10000, &matrices, &fout);
    matrices.pop_back();
    matrices.push_back(Matrix(rows, std::vector<int>(columns, 0)));
    pthreadRoutine(rows*columns/10, &matrices, &fout);
    matrices.pop_back();

    fout.close();
    return 0;
}
