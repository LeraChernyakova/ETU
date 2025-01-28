#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int main()
{
    printf("Son's params: pid = %d, ppid = %d\n", getpid(), getppid());
    while (1)
        pause();
    return 0;
}
