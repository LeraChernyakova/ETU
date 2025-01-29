#include <fstream>
#include "LockFreeQueue.h"
#include "matrix.h"
#include "string"
#include <thread>
using namespace std;

const std::string OUTPUT = "C.txt";

template< class T >
void matricesGenerate(T& queueA, T& queueB, int countIterations, int index, int shiftProducer, int N) 
{
    for (int i = index; i < countIterations; i+= shiftProducer)
    {
        Matrix first = Matrix(N,N); 
        Matrix second = Matrix(N,N);
        queueA.push(first); 
        queueB.push(second);
    }
}

void Multiple(Matrix& first, Matrix& second, Matrix& result, int shiftRow, int threadCount)
{
    first.multiple(second,result,shiftRow,threadCount);
}

template< class T >
void matricesMultiple(T& queueA, 
                    T& queueB, 
                    T& queueC, 
                    int countIterations,
                    int index, 
                    int shiftConsumer, 
                    int N, 
                    int countThreads, 
                    ostream& res)
{
    for (int i = index; i < countIterations; i+= shiftConsumer)
    {
        Matrix A = Matrix(); // извлекаем матрицы
        Matrix B = Matrix();
        bool Aflag = queueA.pop(A);
        bool Bflag = queueB.pop(B);
        if (!Aflag || !Bflag)
        {
            return ;
        }
        Matrix result = Matrix(N,N);
        std::vector<std::thread> multipleThreads = std::vector<std::thread>(countThreads);
        for (int index = 0; index < countThreads; index++) 
        {
            multipleThreads[index] = std::thread(Multiple,
        				std::ref(A),
        				std::ref(B),
                        std::ref(result),
                        index,countThreads); 
        }
        for(auto& thread: multipleThreads) 
        {
            thread.join();
        }
        res << result << '\n';
    }
}

template< class T >
void writeResult(T& queueC, int countIterations, ostream& res)
{
    for (int i = 0; i < countIterations; i++)
    {
        Matrix result = queueC.pop();
        res << result << '\n';
    }
};

int main()
{
    int countProducers = 4;
    int countConsumers = 4;
    int N = 10; // размерность матриц
    int choice = 1; // выбор
    int countThreads = 4; 
    int countIterations = 1000;
    std::vector<std::thread> Producers = std::vector<std::thread>(countProducers);
    std::vector<std::thread> Consumers = std::vector<std::thread>(countConsumers);

    LockFreeQueue queueA = LockFreeQueue();
    LockFreeQueue queueB = LockFreeQueue();
    LockFreeQueue queueC = LockFreeQueue();
    ofstream res_matrix;
    res_matrix.open(OUTPUT);
       
    for (int index = 0; index < countProducers; index++) 
    {
        Producers[index] = std::thread (matricesGenerate<LockFreeQueue>, 
        			ref(queueA), 
          			ref(queueB), 
           			countIterations,
                    index,
                    countProducers, 
                    N);
    }
    for (int index = 0; index < countConsumers; index++) 
    {            
        Consumers[index] = std::thread(matricesMultiple<LockFreeQueue>, 
          			ref(queueA), 
           			ref(queueB), 
           			ref(queueC), 
          			countIterations,
           			index,
           			countConsumers, 
           			N, 
           			countThreads,
           			ref(res_matrix));
    }
    for(auto& thread: Producers) 
    {
        thread.join();
    }
    for(auto& thread: Consumers) 
    {
        thread.join();
    }
    res_matrix.close();
    return 0;
}

