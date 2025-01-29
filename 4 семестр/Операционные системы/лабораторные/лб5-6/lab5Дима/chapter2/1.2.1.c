#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void (*mysig(int sig, void (*hnd)(int)))(int)
{
    //надежная обработка сигналов
    struct sigaction act, oldact;
    //задает тип действий процесса
    act.sa_handler = hnd;
    //инициализирует набор сигналов, указанный в set, и "очищает" его от всех сигналов
    //задает маску сигналов, которые должны блокироваться при обработке сигнала
    sigemptyset(&act.sa_mask);
    //добавляют сигналы signum к set
    sigaddset(&act.sa_mask, SIGINT);
    //содержит набор флагов, которые могут влиять на поведение процесса при обработке сигнала
    act.sa_flags = 0;
    //используется для изменения действий процесса при получении соответствующего сигнала
    if (sigaction(sig, &act, 0) < 0)
        return SIG_ERR;
    return act.sa_handler;
}

void hndUSR1(int sig)
{
    if (sig != SIGUSR1)
    {
        printf("Catched bad signal %d\n", sig);
        return;
    }
    printf("SIGUSR1 catched\n");
    sleep(10);
}

int main()
{
    mysig(SIGUSR1, hndUSR1);
    for (;;)
    {
        pause();
    }
    return 0;
}
