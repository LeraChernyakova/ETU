#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void sigHandler(int sig) {
       printf("Catched signal %s\n",sig == SIGUSR1 ? "SIGUSR1": "SIGUSR2");
       printf("Parent = %d\n",getppid());

       // востанавливаем старую диспозицию
       signal(sig,SIG_DFL);
}
int main() {
       printf("\nFather started: pid = %i,ppid = %i\n",getpid(),getppid());
       signal(SIGUSR1,sigHandler);
       signal(SIGUSR2,sigHandler);
       signal(SIGINT,SIG_DFL);
       signal(SIGCHLD,SIG_IGN);
       int forkRes = fork();

       if(forkRes == 0) {
               // программа-потомок
               printf("\nSon started: pid = %i,ppid = %i\n",getpid(),getppid());
               // отправляем сигналы родителю
               if(kill(getppid(),SIGUSR1) != 0) {
                       printf("Error while sending SIGUSR1\n");
                       exit(1);
               }
               printf("Successfully sent SIGUSR1\n");
               return 0;
       }

       // программа-родитель
       wait(NULL);
       // ждем сигналов
       for(;;){
               pause();
       }

       return 0;
}

