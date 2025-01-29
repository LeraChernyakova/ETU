#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <strings.h>
#include <string.h>
#include "shm.h"


int main(int argc, char** argv) {
    Message* p_msg;
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
    if((shmemory = shmget(key, sizeof(Message), 0666)) < 0) {
        printf("Can't create shm\n");
        exit(1);
    }
    //присоединяем shm в наше адресное пространство
    if((p_msg = (Message*)shmat(shmemory, 0, 0)) < 0) {
        printf("Error while attaching shm\n");
        exit(1);
    }
    if((semaphore = semget(key, 2, 0666)) < 0) {
        printf("Error while creating semaphore\n");
        exit(1);
    }
    char buf[100];
    for(;;) {
        bzero(buf,100);
        printf("Type message to serever. Empty string to finish\n");
        fgets(buf,100,stdin);
        if(strlen(buf) == 1 && buf[0] == '\n') {
            printf("bye-bye\n");
            exit(0);
        }
        //хотим отправить сообщение
        if(semop(semaphore, writeEna, 1) < 0) {
            printf("Can't execute a operation\n");
            exit(1);
        }
        //запись сообщения в разделяемую память
        sprintf(p_msg->buf,"%s", buf);
        //говорим серверу, что он может читать
        if(semop(semaphore, setReadEna, 1) < 0) {
            printf("Can't execute a operation\n");
            exit(11);
        }
    }
    //отключение от области разделяемой памяти
    if(shmdt(p_msg) < 0) {
        printf("Error while detaching shm\n");
        exit(1);
    }
}
