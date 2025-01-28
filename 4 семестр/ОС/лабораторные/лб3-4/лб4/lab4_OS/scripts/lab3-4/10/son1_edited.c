#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
int main()
{
    struct sched_param shdprm; // Значения параметров планирования
    int i, pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("pid=%i ppid=%i ", pid, ppid);
    printf("pol: ");
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
    //if (sched_getparam(0, &shdprm) == 0)
//	printf ("SON_1: Текущий приоритет текущего процесса: %d\n", shdprm.sched_priority);
  //  else
//	perror ("SCHED_GETPARAM");
    return -1;
}
