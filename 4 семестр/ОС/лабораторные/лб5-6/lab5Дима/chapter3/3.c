#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MAX_SIGNALS 10

void handler(int sig, siginfo_t *si, void *ucontext)
{
    printf("Received signal %d with value %d.\n", sig, si->si_value.sival_int);
}

int main()
{
    pid_t pid = getpid();
    sigset_t mask;
    sigemptyset(&mask);

    // Настраиваем обработчик сигнала SIGUSR1
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Создаем массив для хранения значений для sigqueue
    int values[MAX_SIGNALS];
    for (int i = 0; i < MAX_SIGNALS; i++)
    {
        values[i] = i + 1;
    }

    // Отправляем сигналы без задержки
    for (int i = 0; i < MAX_SIGNALS; i++)
    {
        sigqueue(pid, SIGUSR1, (union sigval){.sival_int = values[i]});
    }

    // Обрабатываем сигналы с использованием задержки
    for (int i = 0; i < MAX_SIGNALS; i++)
    {
        usleep(1000000);
    }

    return EXIT_SUCCESS;
}