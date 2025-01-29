#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid = getpid();
    pid_t ppid = getppid();
    printf("Child process is started!\n");
    printf("PPID: %d, PID: %d\n", ppid, child_pid);
    
    kill(ppid, SIGTRAP);
    printf("Signal SIGTRAP is sended by son!\n");

    while(1) {sleep(2);}
    return 0;
}
