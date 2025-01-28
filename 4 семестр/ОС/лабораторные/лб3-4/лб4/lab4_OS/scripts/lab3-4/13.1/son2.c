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
    printf("SON_2 PARAMS: pid=%i ppid=%i\n", pid, ppid);
    for(int signum = 1; signum <=31 ; signum++){
	    signal(signum, SIG_IGN);
    }
    sleep(10);
    return 0;
}
