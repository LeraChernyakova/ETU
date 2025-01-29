#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<time.h>
#include<unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>


int main(){
    key_t key = ftok("son",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);

    struct sched_param shdprm;
   	int pid, ppid;
   	pid = getpid();
   	ppid = getppid();
    int k=2;
    switch (sched_getscheduler (0)) {
			 case SCHED_FIFO:
                /*
                for(int i=0;i<100000000;i++){
                    k*=k;
                }
                */
           		 strcat(str,"F\n");
           		 break;
           	case SCHED_RR:
                /*
                for(int i=0;i<100000000;i++){
                    k*=k;
                }
                */
                strcat(str,"R\n");
                break;
           	case SCHED_OTHER:

                strcat(str,"OTHER\n");
                break;
           	case -1:
                perror ("SCHED_GETSCHEDULER");
                break;
           	default:
                strcat(str,"Неизвестная политика планирования\n");

   	}

    shmdt(str);
    return 0;
}
