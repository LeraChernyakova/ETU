#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include "queueLockFree.h"
#include "Matrix.h"
#include <thread>
using namespace std;
void consoleMatrix(Matrix val){ // вывод матрицы в консоль
    std::cout << "|||||Начало создания|||||" <<std::endl;
    for (int i = 0; i < val.matrix.size(); i++) {
        for (int j = 0;j < val.matrix[0].size();j++) {
        std::cout << val.matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "|||||Конец создания|||||" <<std::endl;
}


template< class T >
void matricesGenerate(T& queueFirst, T& queueSecond, int countIterations,int index,int shiftProducer, int N) // функция создания матриц
{
    for (int i = index; i < countIterations; i+= shiftProducer)
    {

        Matrix first = Matrix(N,N); 
        Matrix second = Matrix(N,N); // выделение памяти под матрицы
        //consoleMatrix(first);
        queueFirst.produce(first); // передать матрицы в продюсера
        queueSecond.produce(second);
    }
}





void Multiple(Matrix& first, Matrix& second,Matrix& result,int shiftRow,int threadCount){ // вызов многопоточного умножения
     first.multiple(second,result,shiftRow,threadCount);
}

template< class T >
void matricesMultiple(T& queueFirst, T& queueSecond, T& queueResult, int countIterations,int index, int shiftConsumer, int N, int countThreads, ostream& res)
{
    
    for (int i = index; i < countIterations; i+= shiftConsumer)
    {
        Matrix first = Matrix();
        Matrix second = Matrix();
        bool firstflag = queueFirst.consume(first); // извлекаем матрицу из очереди
        bool secondflag = queueSecond.consume(second); // извлекаем матрицу из очереди
        //consoleMatrix(first);     
       // consoleMatrix(second);
       if(!firstflag || !secondflag){
        return;
       }
        Matrix result = Matrix(N,N);
        std::vector<std::thread> multipleThreads = std::vector<std::thread>(countThreads); // вектор из P потоков
     for (int index = 0; index < countThreads; index++) {
        multipleThreads[index] = std::thread(Multiple,std::ref(first),std::ref(second),std::ref(result),index,countThreads); // создать потоки для суммы
    }
    for(auto& thread: multipleThreads) {
        thread.join(); // дождаться завершения
    }
        res << result << '\n';
        consoleMatrix(result);
        //queueResult.produce(result); // записываем результат в продюсера 
    }
}




template< class T >
void writeResult(T& queueResult, int countIterations, ostream& res) // записываем матрицу в файл
{
    for (int i = 0; i < countIterations; i++)
    {
        Matrix result = queueResult.consume(); // достаём результат из очереди
        //consoleMatrix(result); 
        res << result << '\n'; // печатаем в файл
    }
};
 


int main(int argc, char *argv[]){
   
    int countIterations; // количество операций умножения
    int countProducers;
    int countConsumers;
    int N; // размерность матриц
    int countThreads; // количество потоков для умножения
    std::cout << "Введите размерность матриц:\n"; 
    cin >> N; //  размерности матриц и количество итераций
    std::cout << "Введите количество потоков:\n";
    cin >> countThreads;  // считывает количество потоков 
    std::cout << "Введите количество итераций:\n";
    cin >> countIterations; // количество итераций
    std::cout << "Введите количество продюсеров:\n";
    cin >> countProducers; // количество продюсеров
    std::cout << "Введите количество консьюмеров:\n";
    cin >> countConsumers; // количество консьюмеров
    std::vector<std::thread> Producers = std::vector<std::thread>(countProducers); // Производители
    std::vector<std::thread> Consumers = std::vector<std::thread>(countConsumers); // Потребители
      auto startTime = std::chrono::steady_clock::now(); // засекаем время начала 
      QueueLockFree queueFirst = QueueLockFree();
      QueueLockFree queueSecond = QueueLockFree();
      QueueLockFree queueResult = QueueLockFree();
      ofstream res_matrix;
      res_matrix.open("result.txt"); // открыть файл результата
      for (int index = 0; index < countProducers; index++) {
            Producers[index] = std::thread(matricesGenerate<QueueLockFree>, ref(queueFirst), ref(queueSecond), countIterations,index,countProducers, N); // создать потоки для суммы
        }
        for(auto& thread: Producers) {
            thread.join(); // дождаться завершения
        }
    for (int index = 0; index < countConsumers; index++) {
            Consumers[index] = std::thread(matricesMultiple<QueueLockFree>, ref(queueFirst), ref(queueSecond), ref(queueResult), countIterations,index,countConsumers, N, countThreads,ref(res_matrix)); // создать потоки для суммы
        }
        for(auto& thread: Consumers) {
            thread.join(); // дождаться завершения
        }
      res_matrix.close();
      std::chrono::duration<double> endTime = std::chrono::steady_clock::now() - startTime; // закончить время подсчёта
      std::cout << "Время работы: " << endTime.count() << " секунд" << std::endl;
      return 0;
    
}
