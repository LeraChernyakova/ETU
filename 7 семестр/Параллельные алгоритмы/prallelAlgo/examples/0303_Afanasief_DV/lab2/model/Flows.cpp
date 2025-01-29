#include "Flows.h"

void Flows::reader() {
    for(int i = 0; i < this->iterationsProducer; i++){
        Matrix left = Matrix::generate(sizeMatrix);
        Matrix right = Matrix::generate(sizeMatrix);
        queueMatrix.push(std::make_pair(left, right));
    
}

void Flows::multiplier() {
    for(int k = 0; k < this->iterationsConsumer; k++) {
        std::pair<Matrix, Matrix> matrixs = queueMatrix.pop();
        MultiplicationMatrix mul = MultiplicationMatrix::create(matrixs.first, matrixs.second);
        Matrix resultMatrix;
        for (int i = 0; i < matrixs.first.size().first; i += threads) {
            int count = threads;
            if (count + i > matrixs.first.size().first) {
                count = matrixs.first.size().first - i;
            }
            std::vector<std::future<std::vector<int>>> futures;
            for (int j = 0; j < count; j++) {
                futures.push_back(std::async(std::launch::async, &MultiplicationMatrix::multiplyRow, &mul, i + j));
            }
            for (auto &res: futures) {
                resultMatrix.m.push_back(res.get());
            }
        }
        queueResult.push(resultMatrix);
    }
}

void Flows::writer() {
    for(int i = 0; i < this->iterationsProducer; i++){
        Matrix m = queueResult.pop();
        std::ofstream file("../result.txt");
        file << m;
        file.close();
    }
}

Flows::Flows(int iterations, int consumers, int producers) : iterationsProducer(iterations), consumers(consumers), producers(producers){
    iterationsConsumer = (iterations*producers)/consumers;
}

void Flows::run() {
    auto start = std::chrono::steady_clock::now();
    std::vector<std::thread> threads;
    for(int i = 0; i < producers; i++){
        threads.emplace_back(&Flows::reader, this);
        threads.emplace_back(&Flows::writer, this);
    }
    for(int i = 0; i < consumers; i++){
        threads.emplace_back(&Flows::multiplier, this);
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
}
