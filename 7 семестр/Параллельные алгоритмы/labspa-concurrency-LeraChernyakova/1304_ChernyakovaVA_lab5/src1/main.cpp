#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <chrono>
#include <cassert>
#include "./matrix.h"

#define MATRIX 1024
#define THREAD 7

double measureTime(const std::string& algorithmName, const std::function<void()>& f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << algorithmName << " | Время выполнения: " << duration << " миллисекунд" << std::endl;
    return duration;
}

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));

    Matrix m1 = createMatrix(MATRIX, MATRIX);
    Matrix m2 = createMatrix(MATRIX, MATRIX);
    Matrix result1, result2, result3;

    measureTime("simple", [&m1, &m2, &result1](){ result1 = parallelSimple(m1, m2, THREAD); });
    measureTime("parallel", [&m1, &m2, &result2](){ result2 = parallelBlocks(m1, m2, THREAD); });
    measureTime("strassen",[&m1, &m2, &result3](){ result3 = strassenMatrixMult(m1, m2); });

    assert( result1 == result2 );
    assert( result2 == result3 );    

    return 0;
}