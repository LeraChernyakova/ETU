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

    if ((sigaction(SIGRTMIN + 1, &action, NULL) < 0)
     || (sigaction(SIGRTMIN + 2, &action, NULL) < 0)
     || (sigaction(SIGRTMIN + 3, &action, NULL) < 0)) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    send_real_time_signal(1, 0);
    send_real_time_signal(2, 1);
    send_real_time_signal(3, 2);
    send_real_time_signal(1, 3);
    send_real_time_signal(2, 4);
    send_real_time_signal(3, 5);
    send_real_time_signal(3, 6);
    send_real_time_signal(2, 7);
    send_real_time_signal(1, 8);
    send_real_time_signal(3, 9);

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
