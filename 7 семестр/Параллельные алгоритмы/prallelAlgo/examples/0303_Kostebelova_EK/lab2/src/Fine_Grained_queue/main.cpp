//2.2 Использовать очередь с “тонкой” блокировкой.
#include "finegrained_queue.cpp"
#include "matrix.h"
#include <thread>
#include <iostream>
#include <chrono>
const char* name = "C:/Users/liza/Documents/PA_Lab2_Kostebelova_0303_Fine_Grained_queue/result.txt";
const int MATRIX_SIZE = 100;
const int PRODUCERS_NUM = 10;
const int CONSUMERS_NUM = 10;


void producer(finegrained_queue<std::pair<Matrix, Matrix>> &queueMatrices, bool &finished, int &generated) {
    while (!finished) {
        queueMatrices.add(std::pair<Matrix, Matrix>(Matrix(MATRIX_SIZE), Matrix(MATRIX_SIZE)));
        generated++;
    }
}

void consumer(finegrained_queue<std::pair<Matrix, Matrix>> &queueMatrices, finegrained_queue<Matrix> &queueResults, bool &finished, int &multiplied
) {
    while (!finished) {
        auto matrices = queueMatrices.get();
        Matrix result = matrices.first * matrices.second;
        queueResults.add(result);
        multiplied++;
    }
}

void writer(finegrained_queue<Matrix> &queueResults, std::ofstream& file, bool &finished, int &printed) {
    while(!finished) {
        Matrix result = queueResults.get();
        file << result;
        printed++;
    }
}

int main() {
    srand(time(NULL));

    int generated = 0;
    int multiplied = 0;
    int printed = 0;

    bool finished = false;

    std::ofstream file;
    file.open(name);
    if (!file.is_open()) exit(-1);

    finegrained_queue<std::pair<Matrix, Matrix>> queueMatrices;
    finegrained_queue<Matrix> queueResults;

    std::vector<std::thread> threads;

    for (int i = 0; i < PRODUCERS_NUM; i++) {
        threads.push_back(std::thread(producer, std::ref(queueMatrices), std::ref(finished), std::ref(generated)));
    }

    for (int i = 0; i < CONSUMERS_NUM; i++) {
        threads.push_back(std::thread(consumer, std::ref(queueMatrices), std::ref(queueResults), std::ref(finished), std::ref(multiplied)));
    }

    threads.push_back(std::thread(writer, std::ref(queueResults), std::ref(file), std::ref(finished), std::ref(printed)));

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    finished = true;

    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    file.close();

    std::cout << "Matrix generated: " << generated << std::endl;
    std::cout << "Matrix multiplied: " << multiplied << std::endl;
    std::cout << "Matrix printed: " << printed << std::endl;

    return 0;
}
