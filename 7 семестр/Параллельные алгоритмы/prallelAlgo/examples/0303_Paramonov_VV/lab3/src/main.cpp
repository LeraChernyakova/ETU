#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdio>

#include "tasks/threads_stage_sep.h"
#include "utils/threads_queue/rough_threads_queue.h"
#include "utils/threads_queue/thin_threads_queue.h"
#include "utils/threads_queue/non_lock_threads_queue.h"

using namespace std;
using namespace std::chrono;

void one_queue_check(int fRows, int fCols, int sRows, int sCols,
                    int numProducers, int numConsumers, int numRepeats,
                    int queueMaxSize, int choice, int numRestarts,
                    string outFileName) {
    baseThreadsQueue<Matrix*>* operationQueue;
    baseThreadsQueue<Matrix>* resultsQueue;
    if (choice == 0) {
        operationQueue = new roughThreadsQueue<Matrix*>(queueMaxSize);
        resultsQueue = new roughThreadsQueue<Matrix>(numRepeats);
    } else if (choice == 1) {
        operationQueue = new thinThreadsQueue<Matrix*>(queueMaxSize);
        resultsQueue = new thinThreadsQueue<Matrix>(numRepeats);
    } else if (choice == 2) {
        operationQueue = new nonLockThreadsQueue<Matrix*>(queueMaxSize);
        resultsQueue = new nonLockThreadsQueue<Matrix>(numRepeats);
    } 

    system_clock::time_point start, end;
    unsigned long sum_duration = 0;

    for (int j = 0; j < numRestarts; j++) {
        start = high_resolution_clock::now();

        vector<thread> allThreads;
        for (int i = 0; i < numProducers; i++) {
            allThreads.push_back(thread(initializeMatrices, fRows, fCols, sRows, sCols, ref(*operationQueue), 
                                        numRepeats, i, numProducers));
        }
        for (int i = 0; i < numConsumers; i++) {
            allThreads.push_back(thread(multiplicateMatrices, ref(*operationQueue), ref(*resultsQueue), 
                                        numRepeats, i, numConsumers));
        }
        allThreads.push_back(thread(outputMatrix, ref(outFileName), ref(*resultsQueue), numRepeats));

        for (int k = 0; k < numProducers + numConsumers; k++) {
            allThreads[k].join();
        }

        end = high_resolution_clock::now();

        allThreads[numProducers + numConsumers].join();

        if (j != numRestarts - 1)
            remove(outFileName.c_str());

        sum_duration += duration_cast<microseconds>(end - start).count();
    }
    
    if (choice == 0) {
        cout << "Rough_queue; ";
    } else if (choice == 1) {
        cout << "Thin_queue; ";
    } else if (choice == 2) {
        cout << "Non_block_queue; ";
    }
    cout << "Num_producers: " <<  numProducers << " ";
    cout << "Num_consumers: " <<  numConsumers << " ";
    cout << "Average_execution_time: " << sum_duration/numRestarts << endl;

    delete operationQueue;
    delete resultsQueue;
}


int main() {
    // Размеры матриц.
    int fRows = 20, fCols = 40;
    int sRows = 40, sCols = 20;

    // Количество продьюсеров и консьюмеров.
    int numProducers = 5;
    int numConsumers = 2;

    // Количество сгенерированных и вычисленных матриц в рамках одного запуска.
    int numRepeats = 200;

    // Максимальный размер очередей на обработку и вывод.
    int queueMaxSize = 50;

    // Количество полных перезапусков (для подсчета среднего времени выполнения при равных параметрах).
    int numRestarts = 100;

    // Имя файла для вывода.
    string outFileName = "output/out_mat.txt";

    // choice: Выбор очереди 0 - грубая блокировка, 1 - тонкая, 2 - без блокировок.
    one_queue_check(fRows, fCols, sRows, sCols, numProducers, numConsumers, numRepeats,
                    queueMaxSize, 0, numRestarts, outFileName);
    one_queue_check(fRows, fCols, sRows, sCols, numProducers, numConsumers, numRepeats,
                    queueMaxSize, 1, numRestarts, outFileName);
    one_queue_check(fRows, fCols, sRows, sCols, numProducers, numConsumers, numRepeats,
                    queueMaxSize, 2, numRestarts, outFileName);

    return 0;
}