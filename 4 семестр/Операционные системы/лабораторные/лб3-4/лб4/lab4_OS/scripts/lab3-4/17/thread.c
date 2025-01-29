#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h>

void* thread_function1(void *arg)
{
    printf("Thread_1 create\n");
    for (int i = 0; i < 10; i++){
        sleep(5);
        printf("Thread_1. %d 5 sec intervals\n", i+1);
    }
    printf("Thread_1 end\n");
    return NULL;
}

void* thread_function2(void *arg)
{
    printf("Thread_2 create\n");
    for (int i = 0; i < 10; i++){
        sleep(1);
        printf("Thread_2. %d 1 sec intervals\n", i+1);
    }
    printf("Thread_2 end\n");
    return NULL;
}
 
int main()
{
    pthread_t thread1, thread2;
    int res1, res2;

    res1 = pthread_create(&thread1, NULL, thread_function1, NULL);
    if (res1 != 0){
        perror("Create 1 flow\n");
        exit(EXIT_FAILURE);
    }

    res2 = pthread_create(&thread2, NULL, thread_function2, NULL);
    if (res2 != 0){
        perror("Create 2 flow\n");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main flow end\n");
    exit(EXIT_SUCCESS);
}