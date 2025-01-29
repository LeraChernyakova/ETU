#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int i = 0;

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
void *thread_func(void *arg) {
    printf("Child thread started.\n");
    /* Do some work here */
    printf("Thread's ");
    switch_policy(sched_getscheduler(0));
    while (i<10){
	    i++;
    }
    printf("Child thread finished.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t child_thread;
    pthread_attr_t attr;
    struct sched_param shdprm;
    int ret;
	
    pid_t pid = getpid();
    shdprm.sched_priority = 1;

    if (sched_setscheduler(pid, SCHED_FIFO, &shdprm) == -1)
    {
        perror("SCHED_SETSCHEDULER");
    }

    printf("Политика процесса: ");
    switch_policy(sched_getscheduler(pid));

    /* Initialize thread attributes */
    ret = pthread_attr_init(&attr);
    if (ret != 0) {
        fprintf(stderr, "pthread_attr_init() failed.\n");
        exit(EXIT_FAILURE);
    }
	
    /* Set thread scheduling to inherit from parent */
    //ret = pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
    ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    if (ret != 0) {
        fprintf(stderr, "pthread_attr_setinheritsched() failed.\n");
        exit(EXIT_FAILURE);
    }

    /* Create child thread with inherited scheduling */
    ret = pthread_create(&child_thread, &attr, thread_func, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create() failed.\n");
        exit(EXIT_FAILURE);
    }

    int thread_policy;
    pthread_attr_getschedpolicy(&attr, &thread_policy);


    /* Wait for child thread to finish */
    pthread_join(child_thread, NULL);

    /* Cleanup thread attributes */
    pthread_attr_destroy(&attr);

    printf("Parent thread exiting.\n");
    return 0;
}
