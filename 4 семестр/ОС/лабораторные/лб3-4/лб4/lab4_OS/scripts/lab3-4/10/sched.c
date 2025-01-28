#include <stdio.h>
#include <sched.h>
int main(void)
{
    struct sched_param shdprm; // Значения параметров планирования
    int pid, pid1, pid2, ppid;
    pid = getpid();
    ppid = getppid();
    printf("FATHER PARAMS: pid=%i ppid=%i\n", pid, ppid);
    shdprm.sched_priority = 50;
    if (sched_setscheduler(0, SCHED_RR, &shdprm) == -1)
    {
        perror("SCHED_SETSCHEDULER");
    }
    if ((pid1 = fork()) == 0)
        execl("son1", "son1", NULL);
    if ((pid2 = fork()) == 0)
        execl("son2", "son2", NULL);
    printf("Текущая политика планирования для текущего процесса: ");
    switch (sched_getscheduler(0))
    {
    case SCHED_FIFO:
        printf("SCHED_FIFO\n");
        break;
    case SCHED_RR:
        printf("SCHED_RR\n");
        break;
    case SCHED_OTHER:
        printf("SCHED_OTHER\n");
        break;
    case -1:
        perror("SCHED_GETSCHEDULER");
        break;
    default:
        printf("Неизвестная политика планирования\n");
    }
    if (sched_getparam(0, &shdprm) == 0)
        printf("Текущий приоритет текущего процесса: %d\n",
               shdprm.sched_priority);
    else
        perror("SCHED_GETPARAM");
    return 0;
}
