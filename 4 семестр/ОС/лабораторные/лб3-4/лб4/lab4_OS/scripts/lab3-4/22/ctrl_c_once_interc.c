#include <stdio.h>
#include <signal.h>
void handler()
{
	puts("^C - signal received");
	signal(SIGINT, SIG_DFL); //восстановление диспозиции по умолчанию
}
int main()
{
	int pid, ppid;
	pid = getpid();
	ppid = getppid();
	printf("Current pid = %d and ppid = %d\n", pid, ppid);
	signal(SIGINT, handler);
	while(1);
	return 0;
}
