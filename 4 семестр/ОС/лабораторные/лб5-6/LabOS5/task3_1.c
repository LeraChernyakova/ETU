#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;

void sigHandler(const int sig, siginfo_t* s, void* ucontext){
	printf("Catched signal %d, counter = %d\n",sig, s->si_value.sival_int);

	int pid = getpid();
	if (sig == SIGRTMAX-2){
		sigqueue(pid, SIGUSR2,(union sigval){.sival_int = counter++});
	}else if (sig == SIGUSR1){
	sigqueue(pid, SIGRTMAX-1,(union sigval){.sival_int = counter++});
	}else if (sig == SIGUSR2){
	sigqueue(pid, SIGRTMAX,(union sigval){.sival_int = counter++});
	}
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
	mysig(SIGUSR1,sigHandler);
	mysig(SIGUSR2,sigHandler);
	mysig(SIGRTMAX,sigHandler);
	mysig(SIGRTMAX-1,sigHandler);
	mysig(SIGRTMAX-2,sigHandler);

	int pid = getpid();
	int sig;
	for(int i=0;i<5;i++){

		sig = (i%2 == 0) ? SIGUSR1 : SIGRTMAX-2;
		sigqueue(pid,sig,(union sigval){.sival_int = counter++});

	}
	sleep(10);
	printf("end\n");
	return 0;
}

