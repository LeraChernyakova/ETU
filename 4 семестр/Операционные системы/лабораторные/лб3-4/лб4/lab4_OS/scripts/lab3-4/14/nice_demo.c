#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int main()
{
    printf("Приоритет = %d\n", getpid(), getpriority(PRIO_PROCESS, getpid()));
    printf("Попытка изменения приоритета на %d\n", 30);
    nice(30);
    printf("Новый приоритет = %d\n",  getpriority(PRIO_PROCESS, getpid()));

    printf("Попытка уменьшения приоритета на %d\n", 20);
    nice(-20);
    printf("Новый приоритет = %d\n", getpriority(PRIO_PROCESS, getpid()));

    printf("Попытка уменьшить приоритет на %d\n", 150);
    nice(-150);
    printf("Новый приоритет = %d\n",  getpriority(PRIO_PROCESS, getpid()));

    return 0;
}