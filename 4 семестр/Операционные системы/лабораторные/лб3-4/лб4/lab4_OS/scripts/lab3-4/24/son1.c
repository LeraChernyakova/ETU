#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>
int main()
{
    struct sched_param shdprm; // Значения параметров планирования
    int i, pid, ppid;
    pid = getpid();
    int k=0;
    ppid = getppid();
    //printf("pid=%i ppid=%i ", pid, ppid);
    //printf("pol: ");
    int schedule = sched_getscheduler(0);
    switch (schedule)
    {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            //    sleep(1);
            break;
        case SCHED_RR:
            //printf("SCHED_RR\n");
            //sleep(5);
            for (int i =0;i<100000000;i++){
                k+=1;
            }
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
    //  printf ("SON_1: Текущий приоритет текущего процесса: %d\n", shdprm.sched_priority);
    //  else
    //  perror ("SCHED_GETPARAM");
    return 0;
}
