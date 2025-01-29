#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int main() {
    // Создаем дочерний процесс
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // В дочернем процессе запускаем программу child_process
        execl("./child_process", "child_process", NULL);

        // Если execl вернулся, значит произошла ошибка
        perror("execl");
        exit(1);
    } else if (child_pid > 0) {
        printf("Parent: child process created with PID %d\n", child_pid);

        // Ожидаем 2 секунды и отправляем сигнал SIGUSR1
        sleep(2);
        printf("Parent: sending SIGUSR1 to child process\n");
        kill(child_pid, SIGUSR1);

        // Ждем завершения дочернего процесса
        int status;
        wait(&status);
        printf("Parent: child process terminated with status %d\n", WEXITSTATUS(status));
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}
