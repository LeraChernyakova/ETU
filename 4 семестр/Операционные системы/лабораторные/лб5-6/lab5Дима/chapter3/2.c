#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define AMOUNT_OF_SIGNALS 10

int counter = 0;
int sig_iter = 0;

void handler(int sig, siginfo_t* si, void* ucontext) {
  printf("Received signal %d with value %d.\n", sig, si->si_value.sival_int);    
  sleep(5);
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
  for (int i = 0; i < AMOUNT_OF_SIGNALS; i++) {
    mysig(SIGRTMIN, handler);
  
  }
  pid_t pid = getpid();
  for (int i = 0; i < AMOUNT_OF_SIGNALS; i++) {
    sigqueue(pid, SIGRTMIN, (union sigval){.sival_int = i});
  }
  return 0;
}