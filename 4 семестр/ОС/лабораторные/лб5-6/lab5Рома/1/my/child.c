#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/syscall.h>

volatile sig_atomic_t running = 1;

void signal_handler(int signum) {
    pid_t tid = syscall(SYS_gettid);
    printf("Поток с TID %d получил сигнал: %d\n", tid, signum);

    if (signum == SIGINT) {
        running = 0;
    }
}

void *child_thread(void *arg) {
    // Установка обработчика сигналов для потока
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    pid_t tid = syscall(SYS_gettid);
    printf("Дочерний поток с TID %d запущен\n", tid);

    // Цикл выполняется, пока переменная running равна 1
    while (running) {
        sleep(1);
    }

    printf("Дочерний поток с TID %d завершен\n", tid);
    return NULL;
}

pthread_t create_child_thread() {
    pthread_t thread_id;
    int status;

    // Создание потока
    status = pthread_create(&thread_id, NULL, child_thread, NULL);
    if (status != 0) {
        perror("pthread_create");
        return 0;
    }

    return thread_id;
}
