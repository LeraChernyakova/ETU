#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
static void sigHandler(int sig) {

      printf("Catched signal %s\n", sig == SIGUSR1 ? "SIGUSR1" : "SIGUSR2");
      printf("Parent = %d\n", getppid());
      signal(sig, SIG_DFL);
}
int main() {
      printf("Father's params: pid = %d, ppid = %d\n", getpid(), getppid());
      signal(SIGUSR1, sigHandler);
      signal(SIGUSR2, sigHandler);
      signal(SIGSTOP, SIG_DFL);
      signal(SIGQUIT, SIG_IGN);
      if (fork() == 0){
              execl("son1", "son1", NULL);
      }
      wait(NULL);
      while(1)
              pause();
      return 0;
}

