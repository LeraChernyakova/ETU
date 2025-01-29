#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

int main(){

    struct sched_param shdprm;
    shdprm.sched_priority = 6;
    int sched;
    for(int i=0;i<6;i++){
   	 int pid = fork();
   	 if(pid<0){
   		 printf("Error creation process\n");
   		 return 1;
   	 }
	 else if (pid == 0){;
   		if(i%2){
   			sched = SCHED_FIFO;
   		}
		else{
   			sched = SCHED_RR;
		}
   		if(sched_setscheduler(0,sched,&shdprm)<0){
   			printf("Error set sched\n");
   			return -1;
   	 	};
   	 	execl("son3","son3",NULL);
   	 	printf("Error execl");
   	 	return -1;
   	 }
    }
    for (int i=0;i<6;i++){
    	wait(NULL);
    }
    return 0;
}
