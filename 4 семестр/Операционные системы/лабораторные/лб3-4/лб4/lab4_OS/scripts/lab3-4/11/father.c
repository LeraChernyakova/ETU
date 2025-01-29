#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
int main(void)
{
    struct sched_param shdprm; // Значения параметров планирования
    struct timespec qp;        // Величина кванта
    int i, pid, pid1, pid2, pid3, ppid, status;
    pid = getpid();
    ppid = getppid();
    printf("FATHER PARAMS: pid=%i ppid=%i\n", pid, ppid);
    shdprm.sched_priority = 50;
    if (sched_setscheduler(0, SCHED_RR, &shdprm) == -1)
        perror("SCHED_SETSCHEDULER_1");
    if (sched_rr_get_interval(0, &qp) == 0)
        printf("Квант при циклическом планировании: %g сек\n",
               qp.tv_sec + qp.tv_nsec / 1000000000.0);
    else
        perror("SCHED_RR_GET_INTERVAL");
    if ((pid1 = fork()) == 0)

    {
        if (sched_rr_get_interval(pid1, &qp) == 0)
            printf("SON: Квант процессорного времени: %g сек\n",
                   qp.tv_sec + qp.tv_nsec / 1000000000.0);
        execl("son", "son", NULL);
    }
    printf("Процесс с pid = %d завершен\n", wait(&status));
    return 0;
}
