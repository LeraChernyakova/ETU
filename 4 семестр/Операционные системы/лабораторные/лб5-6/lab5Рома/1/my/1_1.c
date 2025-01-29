#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
static void sigsegv_handler( int signo );

static void sigtrap_handler(int signo) {
    signal(SIGTRAP, sigtrap_handler);
    printf("Signal SIGTRAP is handled in father!\n");
}

int main(){
    pid_t child_pid;
    pid_t pid = getpid();
    printf( "Father process is started! ");
    printf( "PID: %d\n", pid );
    /* Установка диспозиций сигналов */
    signal( SIGCHLD, SIG_DFL);
    signal( SIGTRAP, sigtrap_handler);
    signal( SIGSEGV, sigsegv_handler);

    if((child_pid = fork()) == 0 ){
        execl("son", "son", NULL);
    }
    else {
        while(1) sleep(2);
    }
    return 0;

}

static void sigsegv_handler(int signo) {
    signal(SIGSEGV, sigsegv_handler);
    printf("Signal SIGSEGV is handled!\n");
}

