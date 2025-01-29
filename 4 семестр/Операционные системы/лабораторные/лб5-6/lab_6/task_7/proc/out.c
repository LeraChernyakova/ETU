#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

int main() {
    // Создаем ключ и получаем идентификатор сегмента разделяемой памяти
    key_t key = ftok("son", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // Получаем указатель на сегмент разделяемой памяти
    char *str = (char*)shmat(shmid, NULL, 0);

    // Выводим строку на экран
    printf("Содержимое сегмента разделяемой памяти:\n%s", str);

    // Отключаемся от сегмента разделяемой памяти
    shmdt(str);

    return 0;
}
