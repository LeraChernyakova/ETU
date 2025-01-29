#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void int_handler()
{
	puts("signal intercepted! some handling");
	signal(SIGTERM, SIG_DFL); //восстановление диспозиции по умолчанию
}

int main()
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("SON_3 PARAMS: pid=%i ppid=%i\n", pid, ppid);
    signal(SIGTERM, int_handler);
    sleep(3);
    return 0;
}
