#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdio>

#include "tasks/threads_stage_sep.h"
#include "utils/threads_queue/rough_threads_queue.h"
#include "utils/threads_queue/thin_threads_queue.h"

using namespace std;
using namespace std::chrono;

mutex printLock;

void pushElements(baseThreadsQueue<int>& queue) {
    for (int i=0; i < 2; i++) {
        queue.push(i);
        printLock.lock();
        cout << "+ Push element " << i << " to queue" << endl;
        printLock.unlock();
    }
}

void popElements(baseThreadsQueue<int>& queue) {
    for (int i=0; i < 2; i++) {
        int elem = queue.pop();
        printLock.lock();
        cout << "- Pop element(" << elem << ") from queue" << endl;
        printLock.unlock();
    }
}


int main() {
    int choice;
    // Размеры матриц.
    int fRows = 20, fCols = 40;
    int sRows = 40, sCols = 20;

    // Количество продьюсеров и консьюмеров.
    int numProducers;
    int numConsumers;

    // Количество сгенерированных и вычисленных матриц в рамках одного запуска.
    int numRepeats = 300;

    // Максимальный размер очередей на обработку и вывод.
    int queueMaxSize = 10;

    // Очереди на обработку и вывод с грубой или тонкой блокировкой.
    baseThreadsQueue<Matrix*>* operationQueue;
    baseThreadsQueue<Matrix>* resultsQueue;

    cout << "Select the blocking type for the matrix multiplication and matrix output queues:" << endl;
    cout << "0 - \"Rough\" blocking" << endl;
    cout << "1 - \"Thin\" blocking" << endl;
    cin >> choice;

    cout << "Enter number of producers:" << endl;
    cin >> numProducers;

    cout << "Enter number of consumers:" << endl;
    cin >> numConsumers;

    if (choice == 0) {
        operationQueue = new roughThreadsQueue<Matrix*>(queueMaxSize);
        resultsQueue = new roughThreadsQueue<Matrix>(queueMaxSize);
    } else {
        operationQueue = new thinThreadsQueue<Matrix*>(queueMaxSize);
        resultsQueue = new thinThreadsQueue<Matrix>(queueMaxSize);
    }   

    // Количество полных перезапусков (для подсчета среднего времени выполнения при равных параметрах).
    int numRestarts = 100;

    // Имя файла для вывода.
    string outFileName = "output/out_mat.txt";

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

        for (int k = 0; k < numProducers + numConsumers + 1; k++) {
            allThreads[k].join();
        }

        end = high_resolution_clock::now();

        if (j != numRestarts - 1)
            remove(outFileName.c_str());

        sum_duration += duration_cast<microseconds>(end - start).count();
    }
    
    if (choice == 0) {
        cout << "Rough_queue; ";
    } else {
        cout << "Thin_queue; ";
    }
    cout << "Num_producers: " <<  numProducers << " ";
    cout << "Num_consumers: " <<  numConsumers << " ";
    cout << "Average_execution_time: " << sum_duration/numRestarts << endl;

    delete operationQueue;
    delete resultsQueue;

    return 0;
}