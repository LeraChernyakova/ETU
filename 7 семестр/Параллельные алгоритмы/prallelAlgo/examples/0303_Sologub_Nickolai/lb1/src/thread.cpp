#include "thread.h"

Thread::Thread(){};

void Thread::Create(Matrix& first, Matrix& second,Matrix& result) // создание матриц
{
    first =  Matrix(this->N,this->M);
    second = Matrix(this->N,this->M);
    result = Matrix(this->N,this->M);

}
void Thread::Multiple(Matrix& first, Matrix& second,Matrix& result,int shiftRow,int threadCount) // умножение матриц
{
if(threadCount == 1){
  first.multiple(second,result);
}
else{
    first.multiple(second,result,shiftRow,threadCount);
}
}
void Thread::outPut(Matrix& result) // вывод результата в файл
{
    result.fileOutput("resultThreads.txt");
}


void Thread::proceedThreads(int choice)
{    
    Matrix first;
    Matrix second;
    Matrix result;
    std::thread create(&Thread::Create,this, std::ref(first),std::ref(second),std::ref(result)); // создать первый поток с созданием матриц
    create.join();  // дождаться завершения потока
    auto startTime = std::chrono::steady_clock::now(); // засечь время начала
    if(choice == 1){
    std::thread multiple(&Thread::Multiple,this,std::ref(first), std::ref(second),std::ref(result),0,1);
    multiple.join();
	}else{
    std::vector<std::thread> multipleThreads = std::vector<std::thread>(threadsCount); // вектор из P потоков
     for (int index = 0; index < threadsCount; index++) {
        multipleThreads[index] = std::thread(&Thread::Multiple,this, std::ref(first), std::ref(second),std::ref(result),index,this->threadsCount); // создать потоки для суммы
    }
    for(auto& thread: multipleThreads) {
        thread.join(); // дождаться завершения
    }
    }
    std::chrono::duration<double> endTime = std::chrono::steady_clock::now() - startTime; // закончить время подсчёта
     std::cout << "Время работы: " << endTime.count() << " секунд" << std::endl;
    std::thread outPut(&Thread::outPut,this, std::ref(result)); // поток вывода информации
    outPut.join();
    
}
