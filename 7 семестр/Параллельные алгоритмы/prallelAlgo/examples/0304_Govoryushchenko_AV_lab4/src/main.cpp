#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <chrono>
#include <cassert>
#include "./matrix.h"

bool readInt(const std::string& str, int& num) {
    try
    {
        num = std::stoi(str);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

double measureTime(const std::function<void()>& f)
{
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main(int argc, char *argv[]) {
    int matrSize;
    std::srand(std::time(nullptr));
    if (argc != 2 || !readInt(argv[1], matrSize))
    {
        std::cerr << "Usage: " << argv[0] << " matrixSize\n";
        return 1;
    }
    if (matrSize & (matrSize - 1)) {
        std::cerr << "matrixSize must be power of 2\n";
        return 1;
    }
    Matrix m1 = createMatrix(matrSize, matrSize);
    Matrix m2 = createMatrix(matrSize, matrSize);
    Matrix result1, result2, result3;

    double time1 = measureTime([&m1, &m2, &result1](){ result1 = m1 * m2; });
    double time2 = measureTime([&m1, &m2, &result2](){ result2 = parallelMatrixMult(m1, m2, 7); });
    double time3 = measureTime([&m1, &m2, &result3](){ result3 = strassenMatrixMult(m1, m2); });

    std::cout << "simple " << time1 << "\n"
        << "P threads " << time2 << "\n"
        << "strassen " << time3 << "\n";

    assert( result1 == result2 );
    assert( result2 == result3 );    

    return 0;
}