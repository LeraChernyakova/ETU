#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <strings.h>
#include <string.h>
#include "shm.h"

int* buf;
int main(int argc, char** argv) {
    char keyFile[100];
    bzero(keyFile,100);
    if(argc < 2) {
        printf("Using default key file %s\n",DEF_KEY_FILE);
        strcpy(keyFile,DEF_KEY_FILE);
    }
    else
        strcpy(keyFile,argv[1]);
    key_t key;
    int shmemory;
    int semaphore;
//будем использовать 1 и тот же ключ для семафора и для shm
    if((key = ftok(keyFile, 'Q')) < 0) {
        printf("Can't get key for key file %s and id 'Q'\n",keyFile);
        exit(1);
    }
    //создаем shm
    if((shmemory = shmget(key, (BUF_SIZE + 1) * sizeof(int), 0666)) < 0)
    {
        printf("Can't create shm\n");
        exit(1);
    }
    //присоединяем shm в наше адресное пространство
    if((buf = (int*)shmat(shmemory, 0, 0)) < 0) {
        printf("Error while attaching shm\n");
        exit(1);
    }
    if((semaphore = semget(key, 2, 0666)) < 0) {
        printf("Error while creating semaphore\n");
        exit(1);
    }
    printf("Press enter to start working\n");
    getchar();
    int send = 0;
    char tb[10];
    int i = 0;
    for(i = 0; i < 5; ++i) {
        //ждем, пока будет хоть одна свободная ячейка
        if(semop(semaphore, waitNotFull, 1) < 0) {
            printf("Can't execute a operation\n");
            exit(1);
        }
        // ждем доступа к разделяемой памяти
        if(semop(semaphore, mem_lock, 1) < 0) {
            printf("Can't execute a operation\n");
            exit(1);
        }
        printf("Add %d to cell %d\n", send, buf[BUF_SIZE]+1);
        ++buf[BUF_SIZE];
        buf[buf[BUF_SIZE]] = send++;
        //освобождаем доступ к памяти
        if(semop(semaphore, mem_unlock, 1) < 0) {
            printf("Can't execute a operation\n");
            exit(11);
        }
        //увеличиваем число занятых ячеек
        if(semop(semaphore, releaseFull, 1) < 0) {
            printf("Can't execute a operation\n");
            exit(11);
        }
    }
    //отключение от области разделяемой памяти
    shmdt(buf);
}

