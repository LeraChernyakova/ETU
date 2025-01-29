#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <utility>
#include <chrono>
#include "matrix.h"
#include "lockfree_queue.cpp"
const char* name = "C:/Users/liza/Documents/PA_Lab3_Kostebelova_0303_Lock_Free_queue/result.txt";
const int MATRIX_SIZE = 100;
const int PRODUCERS_NUM = 1;
const int CONSUMERS_NUM = 1;

void consumer(lockfree_queue<pair<Matrix, Matrix>> &queueMatrices, lockfree_queue<Matrix> &queueResults, int &multiplied, bool &finished) {
    pair<Matrix, Matrix> matrices(Matrix(0), Matrix(0));
    while (!finished) {
        if (queueMatrices.get(matrices)) {
            queueResults.add(matrices.first * matrices.second);
            multiplied++;
        }
    }
}


void producer(lockfree_queue<pair<Matrix, Matrix>> &queueMatrices, int &generated, bool &finished) {
    while (!finished) {
        queueMatrices.add(make_pair(Matrix(MATRIX_SIZE), Matrix(MATRIX_SIZE)));
        generated++;
    }

}


void writer(lockfree_queue<Matrix> &queueResults, int &printed, std::ofstream& out, bool &finished) {
    while(!finished) {
        Matrix result(0);
        if (queueResults.get(result)) {
            out << result;
            printed++;
        }
    }
}



int main() {

    lockfree_queue<pair<Matrix, Matrix>> queueMatrices;
    lockfree_queue<Matrix> queueResults;
    bool finished = false;

    std::ofstream file;
    file.open(name);
    if (!file.is_open()) exit(-1);

    int generated = 0;
    int multiplied = 0;
    int printed = 0;


    std::vector<std::thread> threads;

    for (int i = 0; i < PRODUCERS_NUM; i++) {
        threads.emplace_back(producer, std::ref(queueMatrices), std::ref(generated), std::ref(finished));
    }

    for (int i = 0; i < CONSUMERS_NUM; i++) {
        threads.emplace_back(consumer, std::ref(queueMatrices), std::ref(queueResults), std::ref(multiplied), std::ref(finished));
    }

    threads.emplace_back(writer, std::ref(queueResults), std::ref(printed), std::ref(file), std::ref(finished));

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    finished = true;

    for (auto &t: threads) {
        t.join();
    }

    file.close();

    std::cout << "Matrix generated: " << generated << std::endl;
    std::cout << "Matrix multiplied: " << multiplied << std::endl;
    std::cout << "Matrix printed: " << printed << std::endl;
    return 0;
}
