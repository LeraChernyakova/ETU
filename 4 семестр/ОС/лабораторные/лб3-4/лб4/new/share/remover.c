#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

int main() {
    // Создаем ключ и получаем идентификатор сегмента разделяемой памяти
    key_t key = ftok("task1", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // Получаем указатель на сегмент разделяемой памяти
    char *str = (char*)shmat(shmid, NULL, 0);

    // Очищаем содержимое сегмента разделяемой памяти
    memset(str, 0, 1024);

    // Выводим сообщение о очистке сегмента
    printf("Сегмент разделяемой памяти очищен\n");

    // Отключаемся от сегмента разделяемой памяти
    shmdt(str);

    // Удаляем сегмент разделяемой памяти
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
