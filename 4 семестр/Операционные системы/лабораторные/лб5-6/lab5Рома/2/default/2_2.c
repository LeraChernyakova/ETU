#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
void (*mysig(int sig,void (*hnd)(int)))(int) {
// надежная обработка сигналов
    struct sigaction act,oldact;
    act.sa_handler = hnd;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGINT);
    act.sa_flags = 0;
    if(sigaction(sig,&act,0) < 0)
        return SIG_ERR;
    return act.sa_handler;
}
void hndUSR1(int sig) {
    if(sig != SIGUSR1) {
        printf("Catched bad signal %d\n",sig);
        return;
    }
    printf("SIGUSR1 catched, sending SIGINT\n");
    kill(getpid(),SIGINT);
    sleep(10);
}

int main() {
    mysig(SIGUSR1,hndUSR1);
    for(;;) {
        pause();
    }
    return 0;
}
