#include "./fine_grained_queue/fine_grained_queue.cpp"
#include "./matrix/matrix.hpp"
#include <thread>
#include <iostream>
#include <chrono>


void producer(
    int matrix_size,
    FineGrainedQueue<std::pair<Matrix, Matrix>> &pairs,
    bool &stopping,
    int &generated
) {
    while (!stopping) {
        pairs.add(std::pair<Matrix, Matrix>(
            Matrix(matrix_size),
            Matrix(matrix_size)
        ));
        generated++;
    }
}

void consumer(
    FineGrainedQueue<std::pair<Matrix, Matrix>> &pairs,
    FineGrainedQueue<Matrix> &results,
    bool &stopping,
    int &resolved
) {
    while (!stopping) {
        auto pair = pairs.get();
        Matrix result = pair.first * pair.second;
        results.add(result);
        resolved++;
    }
}

void writer(
    FineGrainedQueue<Matrix> &results,
    std::ofstream& out,
    bool &stopping,
    int &outputed
) {
    while(!stopping) {
        Matrix result = results.get();
        out << result;
        outputed++;
    }
}

int main() {
    srand(time(NULL));
    int matrix_size = 20;
    int producers = 1;
    int consumers = 1;

    int generated = 0;
    int resolved = 0;
    int outputed = 0;

    bool stopping = false;

    std::ofstream out;
    out.open("./data/fine_grained_result.txt");
    if (!out.is_open()) exit(-1);

    FineGrainedQueue<std::pair<Matrix, Matrix>> pairs;
    FineGrainedQueue<Matrix> results;

    std::vector<std::thread> threads;

    for (int i = 0; i < producers; i++) {
        threads.push_back(std::thread(
            producer,
            matrix_size,
            std::ref(pairs),
            std::ref(stopping),
            std::ref(generated)
        ));
    }

    for (int i = 0; i < consumers; i++) {
        threads.push_back(std::thread(
            consumer,
            std::ref(pairs),
            std::ref(results),
            std::ref(stopping),
            std::ref(resolved)
        ));
    }

    threads.push_back(std::thread(
        writer,
        std::ref(results),
        std::ref(out),
        std::ref(stopping),
        std::ref(outputed)
    ));

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    stopping = true;

    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    out.close();

    std::cout << "Generated: " << generated << std::endl;
    std::cout << "Resolved: " << resolved << std::endl;
    std::cout << "Outputed: " << outputed << std::endl;

    return 0;
}