#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>
int main()
{
    struct sched_param shdprm; // Значения параметров планирования
    int pid;
    pid = getpid();
    int k=0;
    int schedule = sched_getscheduler(0);
    switch (schedule)
    {
        case SCHED_FIFO:
            for (int i =0;i<100000000;i++){
                k+=1;
                printf("%iF\n", pid);
            }
            break;
        case SCHED_RR:
            for (int i =0;i<100000000;i++){
                k+=1;
                printf("%iR\n", pid);
            }
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
    return 0;
}
