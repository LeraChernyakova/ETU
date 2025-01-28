#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>


int main()
{
 int pid,pid2,pid3, n;
 pid = fork();
 if (pid == -1)
 {
   error("fork");
   exit(1);
 }

pid2 = fork();
 if (pid2 == -1)
 {
   error("fork");
   exit(1);
 }

 pid3 = fork();
 if (pid3 == -1)
 {
   error("fork");
   exit(1);
 }


key_t key = ftok("task1",65);
int shmid = shmget(key,1024,0666|IPC_CREAT);
char *str = (char*) shmat(shmid,(void*)0,0);

 
while(1){
   	if (pid == 0) {
       		strcat(str,"0\n");
   	 	for(int i=0;i<100;i++){
	       		n*=n;    
   	 	}      		 
   	}
   	if(pid2 == 0){
       		strcat(str,"1\n");
       		for(int i=0;i<1000;i++){
	       		n*=n;
   	 	}
   	}
   	if(pid3 == 0){
       		strcat(str,"2\n");
       		for(int i=0;i<10000;i++){
	       		n*=n;
   	 	}
   	}
  	 
 }
    
 shmdt(str);
 return 0;
}

