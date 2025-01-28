#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int main() {
      printf("Son's params: pid = %d, ppid = %d\n", getpid(), getppid());
      if(kill(getppid(),SIGUSR1)==0){
               printf("Successfully sent SIGUSR1\n");
               return 0;
      }
            
       
      while(1)
              pause();
      return 0;
}

