#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define NUM_SIGNALS 4

void handle_signal(int signo, siginfo_t *info, void *context) {
    printf("Received signal %d with value %d\n", signo, info->si_value.sival_int);
}

int main() {
    int i;
    struct sigaction sa;
    union sigval value;
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    for (i = SIGRTMIN; i <= SIGRTMAX; i++) {
        sigaddset(&sa.sa_mask, i);
    }
    for (i = 1; i <= NUM_SIGNALS; i++) {
        sigaction(SIGINT + i, &sa, NULL);
        sigaction(SIGRTMIN + i, &sa, NULL);
    }

    // Send signals
    for (i = 1; i <= NUM_SIGNALS; i++) {
        value.sival_int = i;
        printf("Sending normal signal %d with value %d\n", SIGINT + i, value.sival_int);
        if (sigqueue(getpid(), SIGINT + i, value) != 0) {
            perror("sigqueue");
            exit(EXIT_FAILURE);
        }
        printf("Sending real-time signal %d with value %d\n", SIGRTMIN + i, value.sival_int);
        if (sigqueue(getpid(), SIGRTMIN + i, value) != 0) {
            perror("sigqueue");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for signals to be processed
    sleep(1);

    return 0;
}

