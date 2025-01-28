#include <stdio.h>
void main(int argc, char *argv[])
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    char command[50];
    sprintf(command, "ps xjf | grep son2 >> %s", argv[1]);
    printf("SON_2 PARAMS: pid=%i ppid=%i\nFather finished before son termination without waiting for it \n",pid,ppid);
    sleep(20);
    ppid=getppid();
    printf("SON_2 PARAMS ARE CHANGED: pid=%i ppid=%i\n",pid,ppid);
    system(command);
}
