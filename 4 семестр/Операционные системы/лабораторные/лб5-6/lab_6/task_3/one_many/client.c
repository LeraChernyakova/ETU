#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

#define DEF_KEY_FILE "key"
typedef struct {
    long type;
    char buf[100];
} Message;
int queue;
int main(int argc, char** argv) {
    key_t key;
    if(argc < 3) {
        printf("Please provide a queue id as an argument\n");
        exit(1);
    } else {
        key = atoi(argv[1]);
    }

    if(key == -1) {
        exit(1);
    }
    queue = msgget(key,0);
    if (queue < 0) {
        printf("Can't create queue\n");
        exit(4);
    }
// основной цикл работы программы
    Message mes;
    int res;
    bzero(mes.buf,100);
    // Auto send a message
    sprintf(mes.buf,"Client %s: Hello, Server!", argv[2]);
    printf("Client %s: Hello, Server!\n", argv[2]);
    mes.type = 1L;
    res = msgsnd(queue,(void*)&mes,sizeof(Message),0);
    if(res != 0) {
        printf("Error while sending msg\n");
        exit(1);
    }
    for(;;) {
        bzero(mes.buf,100);
// читаем сообщение с консоли
        fgets(mes.buf,100,stdin);
        mes.buf[strlen(mes.buf) - 1] = '\0';
// шлем его серверу
        mes.type = 1L;
        res = msgsnd(queue,(void*)&mes,sizeof(Message),0);
        if(res != 0) {
            printf("Error while sending msg\n");
            exit(1);
        }
// получаем ответ, что все хорошо
        res = msgrcv(queue,&mes,sizeof(Message),2L,0);
        if(res < 0) {
            printf("Error while recving msg\n");
            exit(1);
        }
        printf("Server's response: %s\n",mes.buf);
    }
    return 0;
}

