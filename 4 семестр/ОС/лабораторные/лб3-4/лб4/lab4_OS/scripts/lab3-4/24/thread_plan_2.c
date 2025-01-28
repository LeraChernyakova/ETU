#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sched.h>
#include <unistd.h>

pthread_t t1, t2;
void *thread1();
void *thread2();
void switch_policy(int policy);

void main()
{
    int policy1; 
    int policy2;
    struct sched_param param;
    struct sched_param shdprm;
    pid_t pid = getpid();
    
    pthread_attr_t attr_1, attr_2;
    shdprm.sched_priority = 50;

    if (sched_setscheduler(0, SCHED_FIFO, &shdprm) == -1)
    {
        perror("SCHED_SETSCHEDULER");
    }
    printf("Политика процесса: ");
    switch_policy(sched_getscheduler(pid));
    printf("Приоритет процесса: %d\n", shdprm.sched_priority);

    pthread_attr_init(&attr_1);
    pthread_attr_setinheritsched(&attr_1, PTHREAD_INHERIT_SCHED);
    
    pthread_create(&t1, &attr_1, thread1, NULL);
    pthread_attr_getschedparam(&attr_1, &param);
    pthread_attr_getschedpolicy(&attr_1, &policy1);
    printf("Thread_1's priority = %d\n", param.sched_priority);
    printf("Thread_1's ");
    switch_policy(policy1);
    pthread_join(t1, NULL);
    pthread_attr_destroy(&attr_1);
}

void switch_policy(int policy)
{
    switch (policy)
        {
        case SCHED_FIFO:
            printf("policy SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("policy SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("policy SCHED_OTHER\n");
            break;
        case -1:
            perror("policy SCHED_GETSCHEDULER");
            break;
        default:
            printf ("policy Неизвестная политика планирования\n");
        }
}
void *thread2()
{
    int i, count = 0;
    int tid, pid;
    tid = syscall(SYS_gettid);
    pid = getpid();
    printf("Thread_2 with thread id = %d and pid = %d is started\n", tid, pid);
    for (i = 0; i < 10; i++)
    {
        count += 1;
    }
}
void *thread1()
{
    int i, count = 0;
    int tid, pid;
    tid = syscall(SYS_gettid);
    pid = getpid();
    printf("Thread_1 with thread id = %d and pid = %d is started\n", tid, pid);
    for (i = 0; i < 10; i++)
    {
        count += 1;
    }
}
    //param.sched_priority = 10;
    //pthread_attr_setschedparam(&attr_1, &param);
    //param.sched_priority = 30;
    //pthread_attr_setschedparam(&attr_2, &param);
    // Стратегия планирования и связанные с ней атрибуты должны
    // быть взяты из описателя атрибутов, на который указывает
    // аргумент attr
    //pthread_attr_setinheritsched(&attr_1,PTHREAD_EXPLICIT_SCHED);
    //pthread_attr_setinheritsched(&attr_2,PTHREAD_EXPLICIT_SCHED);
    // Стратегия планирования и связанные с ней атрибуты должны
    // быть унаследованы
    //  Установка атрибута наследования от родителя
    // pthread_attr_setinheritsched (&attr_1,
    // PTHREAD_INHERIT_SCHED)
    //  Установка статуса освобождения ресурсов
    // pthread_attr_setdetachstate
    //(&attr, PTHREAD_CREATE_DETACHED);
