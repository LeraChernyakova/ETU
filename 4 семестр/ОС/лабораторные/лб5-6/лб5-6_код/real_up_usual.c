#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int child(void);
int parent(pid_t);

void rt_handler(int signum, siginfo_t *siginfo, void * extra);

int main(){
    pid_t cpid;
    if((cpid == fork()) == 0){
        child();
    }
    else{
        parent(cpid);
    }
}

void rt_handler(int signum, siginfo_t *siginfo, void * extra){
    printf("Received signal %d with value %d.\n", siginfo->si_signo, siginfo->si_int);
    sleep(1);
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

int parent(pid_t cpid){
    union sigval value;
    sleep(3);

    value.sival_int = -10;
    sigqueue(cpid, SIGUSR1, value);
    printf("Sended signal %d value = %d\n", SIGUSR1, value.sival_int);
    sigqueue(cpid, SIGUSR1, value);
    printf("Sended signal %d value = %d\n", SIGUSR1, value.sival_int);

    value.sival_int = SIGRTMAX;
    for (int i = SIGRTMAX; i > SIGRTMIN; i-=10){
        value.sival_int -= 10;
        sigqueue(cpid, i, value);
        printf("Sended signal %d value = %d\n", i, value.sival_int);
    }
}

int child(void){
    mysig(SIGUSR1, rt_handler);
    for (int i = SIGRTMIN; i<= SIGRTMAX; i++){
        mysig(i, rt_handler);
    }
    for(;;){
        pause();
    }
}