#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
void* thread_function1(void *arg);
void* thread_function2(void *arg);
char* get_cur_time();

void *thread_function1(void *arg)
{
    int i;
    system("echo Поток 1 создан >> out_file.txt");
    for (i = 0; i < 10; i++) {
        sleep(5); // Засыпаем на 5 секунд
            }
    system("echo Только первый поток работает >> out_file.txt");
    system("ps -axhf >> out_file.txt");
    system("echo Поток 1 завершен >> out_file.txt");
    return NULL;
}

void *thread_function2(void *arg)
{
    int i;
    system("echo Поток 2 создан >> out_file.txt");
    system("echo Работает первый и второй поток >> out_file.txt");
    system("ps -axhf >> out_file.txt");    
    for (i = 0; i < 20; i++) {
        sleep(1); // Засыпаем на 1 секунду
            }
    system("echo Поток 2 завершен >> out_file.txt");
    return NULL;
}

char *get_cur_time()
{
    time_t mytime = time(NULL);
    char * time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';	
    return time_str;
}


int main()
{
    pthread_t thread1, thread2;
    int result1, result2;
    system("rm out_file.txt");
    // Создание первого потока
    result1 = pthread_create(&thread1, NULL, thread_function1, NULL);
     // Создание второго потока
    result2 = pthread_create(&thread2, NULL, thread_function2, NULL);
  
    //system("echo работают оба потока, вызов ps из main:");
//    system("ps -axhf");
    // Ждем завершения потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    system("echo Главный поток завершен >> out_file.txt");
    exit(EXIT_SUCCESS);
}