#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_t thread1, thread2;

void* thread1_func(void* arg) {
    while (1) {
        printf("Thread 1 is running...\n");
        sleep(1);
    }
    return NULL;
}

void* thread2_func(void* arg) {
    while (1) {
        printf("Thread 2 is running...\n");
        sleep(1);
    }
    return NULL;
}

void signal_handler(int sig) {
    printf("\nSignal caught: %d\n", sig);

    // Остановить выполнение первой нити
    pthread_mutex_lock(&mutex);
    pthread_cancel(thread1);
    pthread_mutex_unlock(&mutex);

    // ... а вторая нить продолжает работу
}

int main() {
    pthread_mutex_init(&mutex, NULL);

    // Создание нитей
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    // Установка обработчика сигнала
    signal(SIGINT, signal_handler);

    // Ожидание нитей
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
