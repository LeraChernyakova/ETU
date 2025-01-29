#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#define PROC_AMOUNT 10
int main() {
    int i;
    char* program = "son1";
    struct sched_param params;
    params.sched_priority = PROC_AMOUNT;
    int sched;
    for (i = 0; i < PROC_AMOUNT; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Ошибка при создании дочернего процесса\n");
            return 1;
            }
            else if (pid == 0) {
                sched = (i % 2 == 0) ? SCHED_FIFO : SCHED_RR;
                if (sched_setscheduler(0, sched, &params) < 0) {
                    printf("Ошибка при установке политики планирования\n";
                    return 1;
            }
            execl(program, program, NULL);
            printf("Ошибка при вызове функции execl\n");
            return 1;
       }
       //else {
        //    wait(NULL);
        //}
    }
    for (int i = 0; i<PROC_AMOUNT;i++){
        wait(NULL);
    }
   return 0;
}