#include "process.h"


enum {N = 5, M = 5};

Process::Process()
{
    this->ProceedProcess();
}

void Process::consoleOutput(int* buf) { // вывод матрицы в консоль через массив
    std::cout << "||||||||Результат||||||||" << std::endl;
    int index = 0;
    for(int i = 0,index = 0;i< N*M; i++) {
        std::cout << buf[i] <<" ";
        index++;
        if(index == N) {
            index = 0;
            std::cout << std::endl;
        }
    }
    std::cout << "|||||||||||||||||||||||||" << std::endl;

}
int  Process::ProceedProcess()
{
    auto startTime = std::chrono::steady_clock::now(); // засекаем время начала    
    ////////////// Первый процесс - создание матриц
    Matrix first(N, M); 
    Matrix second(N,M);
    Matrix result(N,M);
    ////////////// 
    int fd[2]; // массив чтения и записи
    const int read_index  = 0;
    const int write_index = 1;
    if (pipe(fd) < 0) { // создание канала не удалось
        perror("pipe:");
        return 1;
    }
    ////////////// Второй процесс - умножение матриц
    int id = fork();
    if (id == -1) { // создать процесс не удалось
        perror("fork:");
        return 2;
    }
    if (id == 0) {                         // если процесс ребёнка 
        std::cout << "id Процесса:" << getpid()  << std::endl; //получить и вывести id процесса ребёнка
        close(fd[read_index]); // закрыть файловый дескриптор чтения
        first.multiple(second,result); 
        int* buf = result.toArray(); // получить представление результирующей матрицы в виде массива
        write(fd[write_index], (void*)buf,sizeof(int) * N*M); // записать в канал данные
        delete[] buf; // освободить память
        exit(20); // завершение процесса

    }
    close(fd[write_index]); // закрыть файловый дескриптор записи
    int* parent_buf = new int[N * M]; // сгенерировать буффер
    int status = 0; 
    wait(&status);                         //ждём завершение дочернего процесса
    std::cout << "статус процесса ребёнка: " << WEXITSTATUS(status) <<std::endl; // статус процесса ребёнка, ожидаемый 20
    read(fd[read_index], parent_buf,sizeof(int)* N * M);  // читаем из файлового дескриптора, то, что записано первым процессом
    consoleOutput(parent_buf); // проверяем прочитанные данные
    if (pipe(fd) < 0) { // создание канала не удалось
        perror("pipe:");
        return 1;
    }
    ////////////// Третий процесс - вывод результата
    id = fork();
    if (id == -1) { // создать процесс не удалось
        perror("fork:");
        return 2;
    }
    if (id == 0) {                          // если процесс ребёнка 
        int* buf = new int [N* M]; // создаём буффер
        close(fd[write_index]);  // закрываем канал записи
        read(fd[read_index], (void*)buf, sizeof(int) * N*M); // читаем данные из дескриптора
        Matrix out;
        out.fromArray(buf, N, M); // передаём данные в матрицу
        out.fileOutput("multiple_process_result.txt"); // записываем в файл результат
        delete[] buf; // удаляем буфер
        exit(21); 

    }
    close(fd[read_index]); // закрываем канал чтения
    write(fd[write_index], (void*)parent_buf,sizeof(int) * N*M); // записываем буфер в дескриптор
    wait(&status);
    std::cout << "статус процесса ребёнка: " << WEXITSTATUS(status) <<std::endl; // статус процесса ребёнка, ожидаемый 21
    delete[] parent_buf; // удаляем буфер
    std::chrono::duration<double> endTime = std::chrono::steady_clock::now() - startTime;
    std::cout << "Время работы: " << endTime.count() << " секунд" << std::endl;
}

