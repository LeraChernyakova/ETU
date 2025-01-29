#include "../model/Matrix.h"
#include "../model/MultiplicationMatrix.h"
#include <thread>
#include <future>
#include <fstream>
#include <iostream>
#define fromFile

void readMatrix(Matrix& left, Matrix& right){
#ifndef fromFile
    left = Matrix::generate();
    right = Matrix::generate();
#endif
#ifdef fromFile
    std::ifstream file("../input.txt");
    file >> left >> right;
    file.close();
#endif
}

void multiply(Matrix& left, Matrix& right, std::promise<Matrix>& result){
    MultiplicationMatrix mul = MultiplicationMatrix::create(left, right);
    result.set_value(mul.multiply());
}

void writeMatrix(Matrix m){
    std::ofstream file("../result.txt");
    file << m;
    file.close();
}

int main(){
    Matrix left, right;
    std::thread readThread(readMatrix, std::ref(left), std::ref(right));
    readThread.join();
    std::promise<Matrix> promiseResult;
    auto futureResult = promiseResult.get_future();
    std::thread multiplyThread(multiply, std::ref(left), std::ref(right), std::ref(promiseResult));
    Matrix result = futureResult.get();
    std::thread writeThread(writeMatrix,std::ref(result));
    multiplyThread.join();
    writeThread.join();
    return 0;
}