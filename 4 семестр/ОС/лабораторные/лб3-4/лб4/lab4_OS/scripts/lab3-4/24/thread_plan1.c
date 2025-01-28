#include <pthread.h>
#include <stdio.h>
int SIZE = 10;
void switch_policy(int policy);
void* thread_func(void* arg) {
    int prio = *((int*) arg);
    printf("Thread %d  ends work\n", prio);
    
    int dummy = 0;
    for (int i = 0; i < 10; i++){
        dummy++;
    }

    return NULL;
}

int main(void) {

    pthread_attr_t attr;
    struct sched_param param;
    param.sched_priority = 5;
    pthread_t thread_arr[SIZE];
    int prio1 = 1, prio2 = 99;
    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_init(&attr);
    int policy = SCHED_FIFO;

    for (int i = 0; i < SIZE; i++){
        if (i % 2 == 0){
            policy = SCHED_FIFO;
        }    
        else{
            policy = SCHED_RR;
        }
        pthread_attr_setschedpolicy(&attr, policy);
        pthread_create(&thread_arr[i], &attr, thread_func, &i);

        
        pthread_attr_getschedpolicy(&attr, &policy);
        printf("Thread with ");
        switch_policy(policy);
        printf("was created\n");
        
    }
    for (int i = 0; i < SIZE; i++){
        pthread_join(thread_arr[i], NULL);
    }
    pthread_attr_destroy(&attr);
  //  pthread_create(&thread2, NULL, thread_func, &prio2);

    //pthread_join(thread1, NULL);
    

    return 0;
}

void switch_policy(int policy)
{
    switch (policy)
        {
        case SCHED_FIFO:
            printf("policy SCHED_FIFO ");
            break;
        case SCHED_RR:
            printf("policy SCHED_RR ");
            break;
        case SCHED_OTHER:
            printf("policy SCHED_OTHER ");
            break;
        case -1:
            perror("policy SCHED_GETSCHEDULER");
            break;
        default:
            printf ("policy Неизвестная политика планирования ");
        }
}