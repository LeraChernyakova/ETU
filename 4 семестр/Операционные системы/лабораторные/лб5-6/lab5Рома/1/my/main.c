#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/syscall.h>

extern pthread_t create_child_thread();
extern volatile sig_atomic_t running;
extern void signal_handler(int signum);

int main() {
    pthread_t thread_id;
    int status;

    // Создание потока
    thread_id = create_child_thread();
    if (thread_id == 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Установка обработчика сигналов для главного потока
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    pid_t tid = syscall(SYS_gettid);
    printf("Главный поток с TID %d запущен\n", tid);
	sleep(3);

	pthread_kill(thread_id, SIGUSR1);
    pthread_kill(thread_id, SIGUSR2);
	
    // Цикл выполняется, пока переменная running равна 1
    while (running) {
        sleep(1);
    }
	
    printf("Главный поток с TID %d завершен\n", tid);

    // Ожидание завершения дочернего потока
    pthread_join(thread_id, NULL);
    return 0;
}
