#include "matrixfunctions.hpp"

#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
#include <mutex>
#include <optional>

// #define TEST1
// #define TEST2
#define TEST3

auto MATRIX_SIZE = 1 << 13;        //изменяется при запуске функции
size_t STRASSEN_MIN_MATRIX = 1024; //изменяется при запуске функции

using MatrixCoordType = std::uint16_t;
using MatrixCoord = std::pair<MatrixCoordType, MatrixCoordType>;


void strassenMultiplication(Matrix matrix1,
                            Matrix matrix2,
                            Matrix &res,
                            std::uint8_t depth = 0)
{
    auto half = MATRIX_SIZE / std::pow(2, depth + 1);
    if (half <= STRASSEN_MIN_MATRIX)
    {
        res = multiplyMatrix(matrix1, matrix2);
        return;
    }
    auto a11 = slice(matrix1, half, 0, 0);
    auto a12 = slice(matrix1, half, 0, half);
    auto a21 = slice(matrix1, half, half, 0);
    auto a22 = slice(matrix1, half, half, half);

    auto b11 = slice(matrix2, half, 0, 0);
    auto b12 = slice(matrix2, half, 0, half);
    auto b21 = slice(matrix2, half, half, 0);
    auto b22 = slice(matrix2, half, half, half);

    Matrix d = generateMatrix(half);
    Matrix d1 = generateMatrix(half);
    Matrix d2 = generateMatrix(half);
    Matrix h1 = generateMatrix(half);
    Matrix h2 = generateMatrix(half);
    Matrix v1 = generateMatrix(half);
    Matrix v2 = generateMatrix(half);
    if (depth == 0) ///< Параллельное умножение
    {
        std::vector<std::thread> strassenThreads;
        strassenThreads.emplace_back(strassenMultiplication,
                                     a11 + a22,
                                     b11 + b22, std::ref(d), depth + 1);
        strassenThreads.emplace_back(strassenMultiplication,
                                     a12 - a22,
                                     b21 + b22, std::ref(d1), depth + 1);
        strassenThreads.emplace_back(strassenMultiplication,
                                     a21 - a11,
                                     b11 + b12, std::ref(d2), depth + 1);
        strassenThreads.emplace_back(strassenMultiplication,
                                     a11 + a12,
                                     b22, std::ref(h1), depth + 1);
        strassenThreads.emplace_back(strassenMultiplication,
                                     a21 + a22,
                                     b11, std::ref(h2), depth + 1);
        strassenThreads.emplace_back(strassenMultiplication,
                                     a22, b21 - b11,
                                     std::ref(v1), depth + 1);
        strassenThreads.emplace_back(strassenMultiplication,
                                     a11, b12 - b22,
                                     std::ref(v2), depth + 1);

        for (auto &t : strassenThreads)
        {
            t.join();
        }
    }

    else
    {
        auto arg1 = a11 + a22;
        auto arg2 = b11 + b22;
        strassenMultiplication(arg1, arg2, d, depth + 1);
        arg1 = a12 - a22;
        arg2 = b21 + b22;
        strassenMultiplication(arg1, arg2, d1, depth + 1);
        arg1 = a21 - a11;
        arg2 = b11 + b12;
        strassenMultiplication(arg1, arg2, d2, depth + 1);
        arg1 = a11 + a12;
        strassenMultiplication(arg1, b22, h1, depth + 1);
        arg1 = a21 + a22;
        strassenMultiplication(arg1, b11, h2, depth + 1);
        arg2 = b21 - b11;
        strassenMultiplication(a22, arg2, v1, depth + 1);
        arg2 = b12 - b22;
        strassenMultiplication(a11, arg2, v2, depth + 1);
    }
    auto tmp = d + d1;
    tmp = tmp + v1;
    tmp = tmp - h1;
    insert(res, tmp, 0, 0);
    tmp = v2 + h1;
    insert(res, tmp, half, 0);
    tmp = v1 + h2;
    insert(res, tmp, 0, half);
    tmp = d + d2;
    tmp = tmp + v2;
    tmp = tmp - h2;
    insert(res, tmp, half, half);
}

void multiplyVectorMatrixRowbad(Matrix &matrix1,
                                Matrix &matrix2,
                                std::size_t rowIndexStart,
                                std::size_t piece,
                                Matrix &result)
{

    for (auto rowIndex = rowIndexStart; rowIndex < rowIndexStart + piece; ++rowIndex)
    {
        for (auto colIndex = 0; colIndex < result.size(); ++colIndex)
        {
            for (int i = 0; i < MATRIX_SIZE; ++i)
            {
                result[rowIndex][colIndex] += (matrix1[rowIndex][i] * matrix2[i][colIndex]);
            }
        }
    }
}

void badConcurentMultiplication(Matrix &matrix1,
                                Matrix &matrix2,
                                Matrix result,
                                std::size_t matrixSize,
                                std::size_t thNumber)
{
    std::size_t mpiece = matrixSize / thNumber;
    std::vector<std::thread> threads;

    for (auto j = 0; j < thNumber; ++j)
    {
        threads.emplace_back(
            multiplyVectorMatrixRowbad,
            std::ref(matrix1),
            std::ref(matrix2),
            j * mpiece,
            (j == thNumber - 1) && (MATRIX_SIZE % thNumber) ? (mpiece + MATRIX_SIZE % thNumber) : (mpiece),
            std::ref(result));
    }
    for (auto &th : threads)
    {
        th.join();
    }
}

void consume(size_t matrixSize,
             Matrix &matrix1,
             Matrix &matrix2,
             Matrix &result, 
             std::size_t rowIndexStart,
             std::size_t piece)
{
    for(auto i = rowIndexStart; i < rowIndexStart + piece; ++i){
        for (auto j = 0; j < matrixSize; ++j)
        {
            multiplyVectorMatrixRow(i, j, matrix1, matrix2, result);
        }
    }
}

void goodConcurentMultiplication(Matrix &matrix1,
                                 Matrix &matrix2,
                                 Matrix &result,
                                 std::size_t matrixSize,
                                 std::size_t consumersCount)
{
    unsigned piece = matrixSize /  consumersCount;
    unsigned remainder = matrixSize % consumersCount;

    std::vector<std::thread> threads;

    for (auto j = 0; j < consumersCount; ++j)
    {
        threads.emplace_back(consume,
                             MATRIX_SIZE,
                             std::ref(matrix1),
                             std::ref(matrix2),
                             std::ref(result),
                             j*piece,
                             (j == consumersCount - 1) && (remainder != 0) ? piece + remainder : piece
                             );
    }
    for (auto &th : threads)
    {
        th.join();
    }
}

int main()
{
    
    constexpr std::uint8_t minShift{6}; 
    constexpr std::uint8_t maxShift{14}; 
    std::vector<std::chrono::duration<double>> badTime;
    std::vector<std::chrono::duration<double>> goodTime;
    std::vector<std::chrono::duration<double>> strassenTime;
    for(size_t i = minShift; i < maxShift; i++){
        MATRIX_SIZE = 1 << i;
        STRASSEN_MIN_MATRIX = 1 << (i - 4);
        auto matrix1 = generateMatrix(MATRIX_SIZE);
        auto resMatrix = generateMatrix(MATRIX_SIZE);
        
        std::cout << "Перемножение матриц " << MATRIX_SIZE << " x " << MATRIX_SIZE << std::endl; 
        #ifdef TEST1
        auto start = std::chrono::high_resolution_clock::now();
        strassenMultiplication(matrix1, matrix1, resMatrix);
        auto end = std::chrono::high_resolution_clock::now();
        strassenTime.push_back(std::chrono::duration_cast<std::chrono::duration<double>>(end - start));
        #endif
        #ifdef TEST2
        auto start = std::chrono::high_resolution_clock::now();
        badConcurentMultiplication(matrix1, matrix1, resMatrix, MATRIX_SIZE, 19);
        auto end = std::chrono::high_resolution_clock::now();
        badTime.push_back(std::chrono::duration_cast<std::chrono::duration<double>>(end - start));
        #endif
        #ifdef TEST3
        auto start = std::chrono::high_resolution_clock::now();
        goodConcurentMultiplication(matrix1, matrix1, resMatrix, MATRIX_SIZE, 8);
        auto end = std::chrono::high_resolution_clock::now();
        goodTime.push_back(std::chrono::duration_cast<std::chrono::duration<double>>(end - start));
        #endif
    }
    std::cout << "Размер матрицы \t\t" << std::endl;
    auto shift = minShift;
    #ifdef TEST1
    for(const auto& elem: strassenTime){
        MATRIX_SIZE = 1 << shift;
        ++shift;
        std::cout << MATRIX_SIZE << "\t\t" <<  elem.count() << std::endl;
    }
    #endif
    #ifdef TEST2
    for(const auto& elem: badTime){
        MATRIX_SIZE = 1 << shift;
        ++shift;
        std::cout << MATRIX_SIZE << "\t\t" <<  elem.count() << std::endl;
    }
    #endif
    #ifdef TEST3
    for(const auto& elem: goodTime){
        MATRIX_SIZE = 1 << shift;
        ++shift;
        std::cout << MATRIX_SIZE << "\t\t" <<  elem.count() << std::endl;
    }
    #endif

    return 0;
}
