#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define AMOUNT_OF_SIGNALS 10

static volatile int counter = 0;
int sig_iter = 0;

void handler(int sig, siginfo_t* si, void* ucontext) {
  printf("Received signal %d with value %d.\n", sig, si->si_value.sival_int);    
  sleep(1);
}

void (*mysig(int sig, void (*hnd)(int, siginfo_t*, void*)))(int, siginfo_t*, void*) {
    // надежная обработка сигналов
    struct sigaction act, oldact;
    act.sa_sigaction = hnd;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = SA_SIGINFO;
    if (sigaction(sig, &act, &oldact) < 0) {
        perror("sigaction");
        exit(-1);
    }
    return oldact.sa_sigaction;
}

int main() {
  printf("PID: %d\n", getpid());
  mysig(SIGUSR1, handler);
  mysig(SIGRTMIN, handler);  
  for (;;) {
    pause();
  }
  return 0;
}