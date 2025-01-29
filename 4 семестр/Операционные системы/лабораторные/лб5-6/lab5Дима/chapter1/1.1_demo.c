#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
static void sigHandler(int sig)
{
  printf("Catched signal %s\n", sig == SIGUSR1 ? "SIGUSR1" : "SIGUSR2");
  printf("%d", getppid());
  // востанавливаем старую диспозицию
  signal(sig, SIG_DFL);
}
int main()
{
  signal(SIGUSR2, sigHandler);
  FILE* fp;
  fp = fopen("pid_file.txt", "w");
  char str[100];
  if (fp == NULL){
  	perror("FILE");
	exit(1);
  }
  int father_pid = getpid();
  sprintf(str, "%d", father_pid);
  printf("\nFather started: pid = %i\n", father_pid);
  fprintf(fp, str);
  fclose(fp);
  // ждем сигналов
  for (;;)
  {
    pause();
  }
 
  return 0;
}