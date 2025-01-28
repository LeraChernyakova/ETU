#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define REALTIME_SIG SIGRTMIN

void realtime_handler(int sig)
{
    printf("Realtime signal %d received.\n", sig);
}

void normal_handler(int sig)
{
    printf("Normal signal %d received.\n", sig);
}

int main()
{
    struct sigaction sa_realtime, sa_normal;

    // Настройка обработчика для приоритетного сигнала реального времени
    sigemptyset(&sa_realtime.sa_mask);
    sa_realtime.sa_flags = SA_RESTART;
    sa_realtime.sa_handler = &realtime_handler;

    // Настройка обработчика для обычного сигнала
    sigemptyset(&sa_normal.sa_mask);
    sa_normal.sa_flags = SA_RESTART;
    sa_normal.sa_handler = &normal_handler;

    // Установка обработчиков сигналов
    if (sigaction(REALTIME_SIG, &sa_realtime, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
    if (sigaction(SIGINT, &sa_normal, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
  printf("Sending normal signal...\n");
    if (kill(getpid(), SIGINT) == -1) {
        perror("kill");
        return 1;
    }
    printf("Sending realtime signal...\n");
    if (kill(getpid(), REALTIME_SIG) == -1) {
        perror("kill");
        return 1;
    }

  

    sleep(1);

    return 0;
}
