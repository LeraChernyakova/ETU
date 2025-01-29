#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>

long long int OPS_AMOUNT = 1000000000;

void* func_fifo(void* arg) {
    int marker = *((int*) arg);
    int dummy = 0;
    for (int i = 0; i < OPS_AMOUNT; i++) {
        dummy++;
    }
    printf("Thread with SCHED_FIFO END: %d\n", marker);
    pthread_exit(NULL);
}

void* func_rr(void* arg) {
    int marker = *((int*) arg); 
    int dummy = 0;
   for (int i = 0; i < OPS_AMOUNT; i++) {
        dummy++;
    }
    printf("Thread with SCHED_RR END: %d\n", marker);
    pthread_exit(NULL);
}

int main() {
    const int NUM_THREADS = 5;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attrs[NUM_THREADS];
    struct sched_param params[NUM_THREADS];
    int priorityFIFO = 50;
    int priorityRR = 50;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_attr_init(&attrs[i]);
        pthread_attr_setinheritsched(&attrs[i], PTHREAD_EXPLICIT_SCHED);
        if (i % 2 == 0)
            params[i].sched_priority = priorityRR;
        else
            params[i].sched_priority = priorityFIFO;
       // pthread_attr_setschedpolicy(&attrs[i], (i % 2) ? SCHED_RR : SCHED_FIFO);
        pthread_attr_setschedpolicy(&attrs[i], SCHED_RR);
        pthread_attr_setschedparam(&attrs[i], &params[i]);
       // int err = pthread_create(&threads[i], &attrs[i], (i % 2) ? func_rr : func_fifo, NULL);
        int err = pthread_create(&threads[i], &attrs[i], func_rr, &i);
        if (err != 0) {
            printf("Error creating thread %d", i);
        }
    }
 //   puts("");
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished\n");

    return 0;
}