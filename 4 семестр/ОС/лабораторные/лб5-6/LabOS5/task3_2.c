#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;

void sigHandler(const int sig, siginfo_t* s, void* ucontext){
    printf("Catched signal %d, counter = %d\n",sig, s->si_value.sival_int);

   sleep(1);
}

void (*mysig(int sig,void (*hnd)(int,siginfo_t*, void*)))(int, siginfo_t*,void*) {

   	// надежная обработка сигналов
   	struct sigaction act,oldact;
   	act.sa_sigaction = hnd;
   	sigemptyset(&act.sa_mask);
   	sigaddset(&act.sa_mask,SIGINT);
   	act.sa_flags = SA_SIGINFO;
   	if(sigaction(sig,&act,0) < 0)
		return SIG_ERR;
   	return act.sa_sigaction;

}

int main(){
	printf("PID: %d\n",getpid());
	mysig(SIGUSR1,sigHandler);
        mysig(SIGRTMAX,sigHandler);
	for(;;)
		pause();
	

        return 0;
}
