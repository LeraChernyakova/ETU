#include <iostream>
#include <thread>
#include <array>
#include <atomic>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <numeric>
#include <typeinfo>
#include <algorithm>

#include "blockingqueue.hpp"
#include "fineblockingqueue.hpp"
#include "matrixfunctions.hpp"

//DEBUG
#define DEBU

using MatrixCoord = std::pair<std::uint16_t, std::uint16_t>;

using Queue = BlockingQueue<MatrixCoord>;
// using Queue =  FineBlockingQueue<MatrixCoord>;

constexpr size_t MAX_PRODUCERS = 10;
constexpr size_t MAX_CONSUMERS = 10;
constexpr size_t MATRIX_SIZE = 300;
#ifdef DEBUG
std::stringstream produceStream;
std::stringstream consumeStream;
std::mutex rmut;
std::mutex cmut;

#endif

void produce(Queue& q,
             size_t startIndex,
             size_t piece,
             size_t matrixSize)
{
    for (auto i = startIndex; i < startIndex + piece; i++)
    {
        for (auto j = 0; j < matrixSize; j++)
        {
            q.push(std::make_pair(i, j));
            #ifdef DEBUG
            std::unique_lock<std::mutex> lock(rmut);
            produceStream << "push " << i << " " << j << '\n';
            #endif
        }
    }
}

void consume(Queue& q,
             size_t matrixSize,
             Matrix& matrix1,
             Matrix& matrix2,
             Matrix& result,
             size_t counter)
{
    while(counter){
        --counter;
        auto coords = q.pop();
        multiplyVectorMatrixRow(coords.first, coords.second, matrix1, matrix2, result);
        #ifdef DEBUG
        std::unique_lock<std::mutex> lock(cmut);
        // consumeStream << "pop " << coords.first << " " << coords.second << std::endl;
        #endif
    }
}

void prodConsTEST(size_t producersCount, size_t consumersCount){
    Queue q;
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;
    producers.reserve(producersCount);
    consumers.reserve(consumersCount);

    Matrix matrix1 = generateMatrix(MATRIX_SIZE);
    Matrix matrix2 = generateMatrix(MATRIX_SIZE);
    auto res = Matrix();
    res.resize(MATRIX_SIZE, std::vector<long long int>(MATRIX_SIZE));
    
    size_t piece = MATRIX_SIZE / producersCount;
    size_t remainder = MATRIX_SIZE % producersCount;
    for (auto j = 0; j < producersCount; ++j)
    {
        producers.emplace_back(produce, 
                               std::ref(q),
                               j*piece,
                               (j == producersCount - 1) && (remainder != 0) ? piece + remainder : piece ,
                               MATRIX_SIZE);
    }

    auto tmp = MATRIX_SIZE * MATRIX_SIZE; 
    piece =  tmp / consumersCount;
    remainder = tmp % consumersCount;
    for (auto j = 0; j < consumersCount; ++j)
    {
        consumers.emplace_back(consume,
                               std::ref(q),
                               MATRIX_SIZE,
                                std::ref(matrix1),
                                std::ref(matrix1),
                                std::ref(res),
                                (j == consumersCount - 1) && (remainder != 0) ? piece + remainder : piece);
    }
    for(auto& th: producers){
        th.join();
    }
    for(auto& th: consumers){
        th.join();
    }
    #ifdef DEBUG
    std::cout << produceStream.str() << consumeStream.str(); 
    printMatrix(matrix1);
    printMatrix(matrix2);
    std::cout << "\n\nresult\n\n";
    printMatrix(res);

    #endif

}

std::chrono::duration<double> getDuration(size_t producersCount, size_t consumersCount){
    auto start = std::chrono::high_resolution_clock::now();
    prodConsTEST(producersCount, consumersCount);
    auto end = std::chrono::high_resolution_clock::now();
    return std::move(std::chrono::duration_cast<std::chrono::duration<double>>(end - start));
}


int main()
{
    std::cout << "Квадратная матрица размера " << MATRIX_SIZE << " X " << MATRIX_SIZE << std::endl;   
    std::vector<MatrixCoord> counts;
    std::vector<std::chrono::duration<double>> durations;
    size_t exNumber = 1;
    for (size_t i = 1; i <= MAX_PRODUCERS; i++)
    {
        for(size_t j = 1; j <= MAX_CONSUMERS; j++){
            counts.emplace_back(i, j);
            std::cout << "Эксперимент номер:" << exNumber++ << std::endl;
            std::cout << i << " Произ ||| " << j << " Потреб" << '\n';
            durations.push_back(std::move(getDuration(i, j)));
        }
    }
    
    std::cout << "РЕЗУЛЬТАТ\n" << std::endl;

    double avrTime = 0.0;
    for(auto i = 0; i < counts.size(); ++i){
        std::cout << counts[i].first << " Производителей; " << counts[i].second << " Потребителей" << '\n';
        std::cout << "Время " << durations[i].count() << " s" << "\n\n";
        avrTime += durations[i].count();
    }
    avrTime /= durations.size();

    std::cout << "\n\n" << "Среднее значение: " << avrTime << "\n\n";

    std::sort(durations.begin(), durations.end(), [](const std::chrono::duration<double>& a, const std::chrono::duration<double>& b){
       return a.count() < b.count(); 
    });
    std::cout << "\n\n" << "Наименьшие значения:" << "\n\n";
    for(auto i = 0; i < 5; ++i){
        std::cout << "Время " << durations[i].count() << " s" << "\n\n";
    }
    Queue variable;
    std::cout << "\n\n\nИспользовалась матрица типа " << typeid(variable).name() << std::endl;
    
    return 0;
}