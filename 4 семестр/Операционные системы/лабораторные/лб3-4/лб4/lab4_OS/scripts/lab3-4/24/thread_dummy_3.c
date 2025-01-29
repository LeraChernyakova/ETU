#include <pthread.h>
#include <stdio.h>

void* thread_func(void* arg) {
    int prio = *((int*) arg);
    printf("Thread priority: %d\n", prio);
    return NULL;
}

int main(void) {
    pthread_t thread1, thread2;
    int prio1 = 1, prio2 = 99;

    pthread_create(&thread1, NULL, thread_func, &prio1);
    pthread_create(&thread2, NULL, thread_func, &prio2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}