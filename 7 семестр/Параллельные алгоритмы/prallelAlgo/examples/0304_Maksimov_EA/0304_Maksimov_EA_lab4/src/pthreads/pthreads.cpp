#include "pthreads.h"

// При вызове этой функции нужно подготовить объекты. 
// 1. Матрица B должна быть транспонирована.
// 2. В matricesPointer по индексу 2 уже лежит пустая матрица.
void multiplyMatricesMultithreadRoutine(std::vector<Matrix>* matricesPointer, int indexFirst, int indexLast) {
    Matrix A = (*matricesPointer)[0];
    Matrix B = (*matricesPointer)[1];
    int rowsB = B.size();
    for(int i = indexFirst; i < indexLast; i++) {
        (*matricesPointer)[2][i/rowsB][i%rowsB] = multiplyVectors(A[i/rowsB], B[i%rowsB]);
    }

    return;
}

void multiplyMatrciesMultithread(std::vector<Matrix>* matrices, int N) {
    std::vector<std::thread> threads;
    int threadsAmount = int(std::ceil(std::sqrt(N)));
    int threadChunkSize = N*N/threadsAmount;

    // 1. Транспонируем матрицу B.
    (*matrices)[1] = getTransposedMatrix((*matrices)[1]);
    // 2. Создаём пустую матрицу.
    (*matrices).push_back(Matrix(N, std::vector<int>(N, 0)));
    // 3. Добавляем в список потоков все, кроме последнего. В последний поток
    // закидываем то, что нужно было и дополнительно неразделённый остаток.
    for(int i = 0; i < threadsAmount-1; i++) {
        threads.push_back(std::thread(multiplyMatricesMultithreadRoutine, matrices, i*threadChunkSize, (i+1)*threadChunkSize));
    }
    threads.push_back(std::thread(multiplyMatricesMultithreadRoutine, matrices, (threadsAmount-1)*threadChunkSize, N*N));
    // 4. Ожидаем выполнения.
    for(int i = 0; i < threadsAmount; i++) {
        threads[i].join();
    }
}
