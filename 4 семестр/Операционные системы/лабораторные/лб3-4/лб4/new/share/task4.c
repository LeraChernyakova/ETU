#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sched.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

pthread_t t[6];//1, t2,t3,t4;
char answer[10000];
void* fifo(int t_ind){
    char c[3];
  	c[0] = t_ind+'0';
    strcat(answer,c);
    
    strcat(answer,"F\n");
    pthread_exit(NULL);
}

void* rr(int t_ind){
    char c[3];
    c[0] = t_ind+'0';
    strcat(answer,c);
    strcat(answer,"R\n");
    pthread_exit(NULL);
}

void main()
{    
    key_t key = ftok("task1",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
   	 char *str = (char*) shmat(shmid,(void*)0,0);

   	int policy;
   	struct sched_param param[6];
   	pthread_attr_t attr[6];//, attr_2,attr_3,;

    int f = 30;
    int r = 30;
    for(int i=0;i<6;i++){
   	 pthread_attr_init(&attr[i]);
   	 pthread_attr_setinheritsched (&attr[i], PTHREAD_EXPLICIT_SCHED);
   	 if(1){
   		 pthread_attr_setschedpolicy(&attr[i], SCHED_RR);
   		 param[i].sched_priority = r;
   		 pthread_attr_setschedparam(&attr[i], &param[i]);
   		 pthread_create(&t[i], &attr[i], rr,i);
   	 }else{
   		 pthread_attr_setschedpolicy(&attr[i], SCHED_FIFO);
   		 param[i].sched_priority = f;
   		 pthread_attr_setschedparam(&attr[i], &param[i]);
   		 pthread_create(&t[i], &attr[i], fifo,i);
   	 }

/*
    param[i].sched_priority = r;
    
*/
    }
    for(int i=0;i<6;i++){
   	 pthread_join(t[i],NULL);
    }
    strcpy(str,answer);
   	shmdt(str);
    return 0;  	 
}
