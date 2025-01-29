#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int received_signals[10];
int received_signals_value[10];
int received_signals_count = 0;

void real_time_handler(int sig_number, siginfo_t * info,
                       void * arg __attribute__ ((unused)))
{
    received_signals[received_signals_count] = sig_number - SIGRTMIN;
    received_signals_value[received_signals_count] = info->si_value.sival_int;
    ++received_signals_count;
}

void send_real_time_signal(int sig_number, int value)
{
    union sigval sig_value;

    printf("Sending signal SIRTMIN+%d, value %d\n", sig_number, value);
    sig_value.sival_int = value;
    if (sigqueue(getpid(), sig_number + SIGRTMIN, sig_value) < 0) {
        perror("sigqueue");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    struct sigaction action;
    sigset_t set;
    int i;

    // Handler setup
    action.sa_sigaction = real_time_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;

   sigaddset(&action.sa_mask, SIGRTMIN + 1);
   sigaddset(&action.sa_mask, SIGRTMIN + 2);
   sigaddset(&action.sa_mask, SIGRTMIN + 3);

    // Block all signals
    sigprocmask(SIG_BLOCK, &action.sa_mask, NULL);

    int arr[10] = {11, 20, 14, 4, 15, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++)
    if (sigaction(SIGRTMIN + arr[i], &action, NULL) < 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    send_real_time_signal(11, 1);
    send_real_time_signal(20, 1);
    send_real_time_signal(14, 1);
    send_real_time_signal(4, 1);
    send_real_time_signal(15, 1);
    send_real_time_signal(6, 1);
    send_real_time_signal(7, 1);
    send_real_time_signal(8, 1);
    send_real_time_signal(9, 1);
    send_real_time_signal(10, 1);

    // Unblock all signals
    // To make sure we're handling all signals before resuming
    sleep(1);
    sigfillset(&set);
    sigprocmask(SIG_UNBLOCK, &set, NULL);

    // Display results
    for (i = 0; i < received_signals_count; ++i) {
        printf("Received signal SIGRTMIN+%d, value %d\n",
               received_signals[i], received_signals_value[i]);
    }

    return EXIT_SUCCESS;
}
