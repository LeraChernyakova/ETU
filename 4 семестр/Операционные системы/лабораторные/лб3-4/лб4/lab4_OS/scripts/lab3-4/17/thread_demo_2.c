#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

void *thread_function1(void *arg);
void *thread_function2(void *arg);
void sigusr1_handler(int signal_number);
pthread_t thread2;


int main(int argc, char *argv[])
{
    pthread_t thread1;
    int result1;
    // Установка обработчика сигнала SIGUSR1
    signal(SIGUSR1, sigusr1_handler);
    // Создание первого потока
    result1 = pthread_create(&thread1, NULL, thread_function1, NULL);
    // Ожидание завершения первого потока
    pthread_join(thread1, NULL);
    printf("Главный поток завершен\n");
    exit(EXIT_SUCCESS);
}

void *thread_function1(void *arg)
{
    int i;
    printf("Поток 1 создан\n");
    // Создание второго потока
    pthread_create(&thread2, NULL, thread_function2, NULL);
    // Ждем 5 секунд и затем останавливаем второй поток
    sleep(5);
 //   thread2_running = 0;
    pthread_kill(thread2, SIGUSR1);
    // Ожидание завершения второго потока
    pthread_join(thread2, NULL);
    printf("Поток 1 завершен\n");
    return NULL;
}

void *thread_function2(void *arg)
{
    int i = 0;
    printf("Поток 2 создан\n");
    while (1) {
        sleep(1); // Засыпаем на 1 секунду
        printf("Поток 2: %d секундных интервалов\n", ++i);
    }
    return NULL;
}

void sigusr1_handler(int signal_number)
{
    printf("Принят сигнал SIGUSR1.\nПоток 2 завершён\n");
    //pthread_cancel(thread2);
    pthread_exit(NULL);

}
