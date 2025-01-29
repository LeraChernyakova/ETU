#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

void *thread_function1(void *arg);
void *thread_function2(void *arg);
void sigusr1_handler(int signal_number);
pthread_t thread2;

void switch_policy(int policy)
{
    switch (policy)
    {
        case SCHED_FIFO:
            printf("policy SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("policy SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("policy SCHED_OTHER\n");
            break;
        case -1:
            perror("policy SCHED_GETSCHEDULER");
            break;
        default:
            printf("policy Неизвестная политика планирования\n");
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread1;
    int result1;
    pthread_attr_t attr1;

    // Установка обработчика сигнала SIGUSR1
    signal(SIGUSR1, sigusr1_handler);

    pthread_attr_init(&attr1);
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);
    // Установка параметров планирования для первого потока
    struct sched_param shdprm;
    shdprm.sched_priority = 1;
    pthread_attr_setschedparam(&attr1, &shdprm);

    // Создание первого потока
    result1 = pthread_create(&thread1, &attr1, thread_function1, NULL);



    // Ожидание завершения первого потока
    pthread_join(thread1, NULL);
    printf("Главный поток завершен\n");
    exit(EXIT_SUCCESS);
}

void *thread_function1(void *arg)
{
    
    printf("Поток 1 создан\n");
    printf("Политика потока 1: ");
    switch_policy(sched_getscheduler(0));
    //printf("Приоритет потока 1: %d", );


    pthread_attr_t attr2;

    pthread_attr_init(&attr2);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
    //pthread_attr_setinheritsched(&attr2, PTHREAD_INHERIT_SCHED);

    pthread_attr_setschedpolicy(&attr2, SCHED_RR);

    // Установка параметров планирования для второго потока
    struct sched_param param;
    param.sched_priority = 2;
    pthread_attr_setschedparam(&attr2, &param);

    pthread_create(&thread2, &attr2, thread_function2, NULL);

    // Ждем 5 секунд и затем останавливаем второй поток
    sleep(5);
    pthread_kill(thread2, SIGUSR1);

    // Ожидание завершения второго потока
    pthread_join(thread2, NULL);
    printf("Поток 1 завершен\n");

    pthread_attr_destroy(&attr2);
    return NULL;
}

void *thread_function2(void *arg)
{
    printf("Поток 2 создан\n");
    printf("Политика потока 2: ");
    switch_policy(sched_getscheduler(0));
    while (1)
    {
        sleep(1);
    }
    return NULL;
}

void sigusr1_handler(int signal_number)
{
    printf("Поток 2 завершен\n");
    pthread_exit(NULL);
}
