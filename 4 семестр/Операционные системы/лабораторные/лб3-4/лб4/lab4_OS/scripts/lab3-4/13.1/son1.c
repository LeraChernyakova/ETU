#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
int main()
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("SON_1 PARAMS: pid=%i ppid=%i\n", pid, ppid);
  //  while (1);
    sleep(3);
    return 0;
}
