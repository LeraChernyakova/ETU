#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int reg_flag = 0;
static int rt_flag = 0;
static int signal_counter = 0;

const char* switch_int_to_sigstr(int sig){
    if (sig == SIGRTMIN){
        return "SIGRTMIN";
    }
    else if (sig == SIGRTMIN+1){
        return "SIGRTMIN+1";
    }
    else if (sig == SIGRTMIN+2){
        return "SIGRTMIN+2";
    }
    else if (sig == SIGUSR1){
        return "SIGUSR1";
    }
    else if (sig == SIGUSR2){
        return "SIGUSR2";
    }
    return "UNKNOWN";
}

void handler(const int sig, siginfo_t* si, void* ucontext){
    printf("Received signal %s with value %d.\n", switch_int_to_sigstr(sig), si->si_value.sival_int);
    int pid = getpid();
    if (sig == SIGRTMIN){
        sigqueue(pid, SIGUSR2, (union sigval){.sival_int = signal_counter++});
    }
    else if (sig == SIGUSR1){
        sigqueue(pid, SIGRTMIN+1, (union sigval){.sival_int = signal_counter++});
    }
    if (sig == SIGUSR2){
        sigqueue(pid, SIGRTMIN+2, (union sigval){.sival_int = signal_counter++});
    }
}

void (*mysig(int sig, void (*hnd)(int, siginfo_t*, void*)))(int, siginfo_t*, void*){
    //обработка сигнала надёжная
    struct sigaction act, oldact;
    act.sa_sigaction = hnd;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = SA_SIGINFO;
    if (sigaction(sig, &act, &oldact) < 0){
        perror("sigaction");
        exit(-1);
    }
    return oldact.sa_sigaction;
}

int main(void){
    mysig(SIGUSR1, handler);
    mysig(SIGUSR2, handler);
    mysig(SIGRTMIN, handler);
    mysig(SIGRTMIN+1, handler);
    mysig(SIGRTMIN+2, handler);

    int pid = getpid();
    int signal;
    for (int i = 0; i < 12; i++){
        signal = (i%2==0) ? SIGRTMIN : SIGUSR1;
        sigqueue(pid, signal, (union sigval){.sival_int = signal_counter++});
    }

    sleep(5);
    printf("The end of program.\n");
    return EXIT_SUCCESS;
}