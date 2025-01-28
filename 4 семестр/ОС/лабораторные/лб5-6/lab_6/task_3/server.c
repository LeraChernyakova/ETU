#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#define DEF_KEY_FILE "key"

typedef struct {
    long type;
    char buf[100];
} Message;

int queue;
void intHandler(int sig) {
    signal(sig,SIG_DFL);
    if(msgctl(queue,IPC_RMID,0) < 0) {
        printf("Can't delete queue\n");
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
    key = ftok(keyFile,'Q');
    if(key == -1) {
        printf("no got key for the key file %s and id 'Q'\n",keyFile);
        exit(1);
    }
    queue = msgget(key,IPC_CREAT | 0666);
    if (queue < 0) {
        printf("Can't create queue\n");
        exit(4);
    }
    // до этого момента вызывали exit(), а не kill, т.к. очередь
    // еще не была создана
    signal(SIGINT,intHandler);
    // основной цикл работы сервера
    Message mes;
    int res;
    for(;;) {
        bzero(mes.buf,100);
        // получаем первое сообщение с типом 1
        res = msgrcv(queue,&mes,sizeof(Message),1L,0);
        if(res < 0) {
            printf("Error while recving msg\n");
            kill(getpid(),SIGINT);
        }
        printf("Client's request: %s\n",mes.buf);
        // шлем клиенту сообщение с типом 2, что все ок
        mes.type = 2L;
        bzero(mes.buf,100);
        strcpy(mes.buf,"OK");
        res = msgsnd(queue,(void*)&mes,sizeof(Message),0);
        if(res != 0) {
            printf("error while sending msg\n");
            kill(getpid(),SIGINT);
        }
    }   
    return 0;
}