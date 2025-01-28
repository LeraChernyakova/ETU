
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function(void *arg) {
    int prio = *((int*) arg);
    printf("Thread priority: %d\n", prio);
//    sleep(1);
    return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t thread1, thread2;
  pthread_attr_t attr;
  struct sched_param param;
  


  if (argc < 2) {
    printf("Usage: %s <priority1> <priority2>\n", argv[0]);
    return 1;
  }

  int priority1 = atoi(argv[1]);
  int priority2 = atoi(argv[2]);

  // Set the scheduling policy and priority for the newly created pthread
  pthread_attr_init(&attr);
  pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
  param.sched_priority = priority1;
  pthread_attr_setschedparam(&attr, &param);

  pthread_attr_init(&attr);
  pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
  param.sched_priority = priority2;
  pthread_attr_setschedparam(&attr, &param);


  // Create the pthread with the specified SCHED_FIFO policy and priority
  if (pthread_create(&thread1, &attr, thread_function, &priority1) != 0) {
    perror("pthread_create");
    return 1;
  }

  if (pthread_create(&thread2, &attr, thread_function, &priority2) != 0) {
    perror("pthread_create");
    return 1;
  }


  printf("Main started\n");
  // Now join the pthread
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("Main end\n");
  return 0;
}
