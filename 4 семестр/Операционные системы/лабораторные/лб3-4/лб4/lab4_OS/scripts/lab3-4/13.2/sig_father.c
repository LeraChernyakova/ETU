#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
static void handler(int sig)
{
    printf("Catched signal %s\n", sig == SIGUSR1 ? "SIGUSR1" : "SIGUSR2");
    printf("Parent = %d\n", getppid());
    signal(sig, SIG_DFL);
}
int main()
{
    printf("Father's params: pid = %d, ppid = %d\n", getpid(), getppid());
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    if (fork() == 0)
        execl("sig_son", "sig_son", NULL);
    wait(NULL);
    while (1)
        pause();
    return 0;
}
