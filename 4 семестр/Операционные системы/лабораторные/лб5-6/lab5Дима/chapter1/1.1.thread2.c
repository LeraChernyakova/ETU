#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

pthread_t thread1;
sigset_t set;

void *thread_func(void *args) {
    printf("Thread started\n");
    while(1) {
        int signum;
        sigwait(&set, &signum);
        printf("Received signal %d\n", signum);
    }
    
    pthread_exit(NULL);
}


void sig_handler(int signum){
	printf("sigusr2 caught\n");
}

int main() {
    signal(SIGUSR2, sig_handler);
    
    sigemptyset(&set);
    sigaddset(&set, SIGTERM);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGUSR2);
    if(pthread_create(&thread1, NULL, thread_func, NULL)) {
        printf("Error creating thread\n");
        return 1;
    }

    printf("Main thread started. PID: %d\n", getpid());
    int i = 0;
    while(1) {
        printf("Main thread running %d\n", i);
        i++;
        sleep(5);
    }

    return 0;
}
