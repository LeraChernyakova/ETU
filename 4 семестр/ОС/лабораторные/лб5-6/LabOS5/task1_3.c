#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

void sigHandler(int sig){}

pthread_t t1;
sigset_t set;
int id;


void *create_thread(void* args){
	id = gettid();
	printf("id: %d\n",id);
	while(1){
		int sig;
		sigwait(&set, &sig);
		printf("Catched signal %s\n",
			 sig == SIGUSR1 ? "SIGUSR1" : "SIGUSR2");
		if (sig == SIGUSR1)
			break;

	}

	printf("t end\n");
	pthread_exit(NULL);

}

int main(){

	
	signal(SIGUSR1, sigHandler);
        signal(SIGUSR2, SIG_IGN);
	sigemptyset(&set);
	sigaddset(&set,SIGSTOP);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGUSR1);
	if(pthread_create(&t1,NULL,create_thread,NULL)){
		printf("Error\n");
		return 1;
	}
	printf("PID: %d\n",getpid());
	int i=0;
	pthread_join(t1,NULL);
	printf("p end\n");
	return 0;
	
}
