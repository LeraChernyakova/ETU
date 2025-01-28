#include <stdio.h>
#include <signal.h>
void handler()
{
        static int i = 0;
        printf("^Z - signal received, i = %d\n", i);
        if (i++ == 5) //количество срабатываний текущего обработчика
                signal(SIGTSTP, SIG_DFL); //восстановление стандартного
//обработчика
}        
int main()
{
        int pid, ppid;
        pid = getpid();
        ppid = getppid();
        printf("Current pid = %d and ppid = %d\n", pid, ppid);
        signal(SIGTSTP, handler);
        while(1);
        return 0;
}
