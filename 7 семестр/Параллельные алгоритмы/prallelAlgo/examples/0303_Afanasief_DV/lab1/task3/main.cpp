#include "../model/Matrix.h"
#include "../model/MultiplicationMatrix.h"
#include <thread>
#include <future>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
//#define fromFile

void readMatrix(Matrix& left, Matrix& right, int size){
#ifndef fromFile
    left = Matrix::generate(size);
    right = Matrix::generate(size);
#endif
#ifdef fromFile
    std::ifstream file("../input.txt");
    file >> left >> right;
    file.close();
#endif
}

void multiplyByThread(Matrix& left, Matrix& right, std::promise<Matrix>& result, int countThreads){
    MultiplicationMatrix mul = MultiplicationMatrix::create(left, right);
    Matrix resultMatrix;
    for(int i = 0; i < left.size().first; i += countThreads){
        int count = countThreads;
        if(count + i > left.size().first){
            count = left.size().first - i;
        }
        std::vector<std::future<std::vector<int>>> futures;
        for(int j = 0; j < count; j++){
            futures.push_back(std::async(std::launch::async, &MultiplicationMatrix::multiplyRow, &mul, i+j));
        }
        for(auto& res : futures){
            resultMatrix.m.push_back(res.get());
        }
    }
    result.set_value(resultMatrix);
}

void writeMatrix(Matrix m){
    std::ofstream file("../result.txt");
    file << m;
    file.close();
}

void test(int quantityThread, int n){
    Matrix left, right;
    std::thread readThread(readMatrix, std::ref(left), std::ref(right), n);
    readThread.join();
    std::promise<Matrix> promiseResult;
    auto futureResult = promiseResult.get_future();
    auto start = std::chrono::steady_clock::now();
    std::thread multiplyThread(multiplyByThread, std::ref(left), std::ref(right), std::ref(promiseResult), quantityThread);
    Matrix result = futureResult.get();
    auto end = std::chrono::steady_clock::now();
    std::cout << "Quantity threads: " << quantityThread << " Matrix size: " << n << "x" << n
        << " Time: " <<std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << '\n';
    multiplyThread.join();
    std::thread writeThread(writeMatrix,std::ref(result));
    writeThread.join();
}

int main(){
    for(int i = 2; i < 1025; i *= 2){
        int k = 1;
        for(int j = 0; j <= 50; j+=5){
            test(k+j, i);
            k = 0;
        }
    }
    return 0;
}