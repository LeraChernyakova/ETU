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


Message* p_msg;
int shmemory;
int semaphore;

void intHandler(int sig) {
    //отключаем разделяемую память
    
    if(shmdt(p_msg) < 0) {
        printf("Error while detaching shm\n");
        exit(1);
    }
    
    //удаляем shm и семафоры
    if(shmctl(shmemory, IPC_RMID, 0) < 0) {
        printf("Error while deleting shm\n");
        exit(1);
    }
    
    if(semctl(semaphore, 0, IPC_RMID) < 0) {
        printf("Error while deleting semaphore\n");
        exit(1);
    }
}
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
    //будем использовать 1 и тот же ключ для семафора и для shm
    if((key = ftok(keyFile, 'Q')) < 0) {
        printf("Can't get key for key file %s and id 'Q'\n",keyFile);
        exit(1);
    }
    //создаем shm
    if((shmemory = shmget(key, sizeof(Message), IPC_CREAT | 0666)) < 0) {
        printf("Can't create shm\n");
        exit(1);
    }
    //присоединяем shm в наше адресное пространство
    if((p_msg = (Message*)shmat(shmemory, 0, 0)) < 0) {
        printf("Error while attaching shm\n");
        exit(1);
    }
// устанавливаем обработчик сигнала
    signal(SIGINT, intHandler);
    //создаем группу из 2 семафоров
    //1 - показывает, что можно читать
    //2 - показывает, что можно писать
    if((semaphore = semget(key, 2, IPC_CREAT | 0666)) < 0) {
        printf("Error while creating semaphore\n");
        kill(getpid(),SIGINT);
    }
    // устнавливаем 2 семафор в 1, т.е. можно писать
    if(semop(semaphore, setWriteEna, 1) < 0) {
        printf("execution complete\n");
        kill(getpid(),SIGINT);
    }
// основной цикл работы
    for(;;) {
// ждем пока клиент начнет работу
        if(semop(semaphore, readEna, 1) < 0) {
            printf("execution complete\n");
            kill(getpid(),SIGINT);
        }
        //читаем сообщение от клиента
        printf("Client's message: %s", p_msg->buf);
        // говорим клиенту, что можно снова писать
        if(semop(semaphore, setWriteEna, 1) < 0) {
            printf("execution complete\n");
            kill(getpid(),SIGINT);
        }
    }
}

