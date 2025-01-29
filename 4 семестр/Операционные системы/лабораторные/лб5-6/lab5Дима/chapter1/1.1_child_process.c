#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Функция-обработчик сигнала SIGUSR1
void sigusr1_handler(int sig) {
    printf("Child: received SIGUSR1\n");
    exit(0); // Завершаем работу
}

int main() {
    printf("Child: process started, waiting for signals\n");

    // Устанавливаем обработчик сигнала SIGUSR1
    signal(SIGUSR1, sigusr1_handler);

    // Ждем входящих сигналов
    while (1) {
        pause();
    }

    return 0;
}
