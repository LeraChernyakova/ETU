#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <sys/mman.h>

#define THREADS_AMOUNT 30
#define OPERATIONS_AMOUNT 100

#define SCHED_TYPE SCHED_OTHER

int *free_index;
int *shared_memory;

void* create_shared_memory(size_t size) 
{
  int protection = PROT_READ | PROT_WRITE;

  int visibility = MAP_SHARED | MAP_ANONYMOUS;

  return mmap(NULL, size, protection, visibility, -1, 0);
}

void *thread_schedule(void *attr)
{
    for (int i = 0; i < OPERATIONS_AMOUNT; i++);
    shared_memory[(*free_index)++] = *((int*)attr);
}

int main()
{
    free_index = create_shared_memory(sizeof(int));
    *free_index = 0;
    shared_memory = create_shared_memory(sizeof(int) * 
THREADS_AMOUNT);
    for (int i = 0; i < THREADS_AMOUNT; i++)
    {
        shared_memory[i] = -1;
    }

    pthread_t threads[THREADS_AMOUNT];
    pthread_attr_t threads_attrs[THREADS_AMOUNT];
    struct sched_param params[THREADS_AMOUNT];
    int priority = 50;
    int thread_id[THREADS_AMOUNT];
    for (int i = 0; i < THREADS_AMOUNT; i++) {
        pthread_attr_init(&threads_attrs[i]);

        pthread_attr_setinheritsched(&threads_attrs[i], 
PTHREAD_EXPLICIT_SCHED);
        params[i].sched_priority = priority;

        pthread_attr_setschedpolicy(&threads_attrs[i], SCHED_TYPE);
        pthread_attr_setschedparam(&threads_attrs[i], &params[i]);
        thread_id[i] = i;
        if(pthread_create(&threads[i], &threads_attrs[i], 
thread_schedule, &thread_id[i]))
        {
            fprintf(stderr, "Error creating thread %d\n", i);
        }
    }
    for (int i = 0; i < THREADS_AMOUNT; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < THREADS_AMOUNT; i++)
    {
        fprintf(stderr, "Thread no %d complited\n", 
shared_memory[i]);
    }

    printf("All threads finished\n");

    return 0;
}