// Client.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#define DEF_KEY_FILE "key"
typedef struct
{
    long type;
    char buf[100];
} Message;
int queue;
int main(int argc, char **argv)
{
    char keyFile[100];
    bzero(keyFile, 100);
    if (argc < 2)
    {
        printf("Using default key file %s\n", DEF_KEY_FILE);
        strcpy(keyFile, DEF_KEY_FILE);
    }
    else
        strcpy(keyFile, argv[1]);
    key_t key;
    key = ftok(keyFile, 'Q');
    if (key == -1)
    {
        printf("no got key for key file %s and id 'Q'\n", keyFile);
        exit(1);
    }
    queue = msgget(key, 0);
    if (queue < 0)
    {
        printf("Can't create queue\n");
        exit(4);
    }
    // основной цикл работы программы
    Message mes;
    int res;
    for (;;)
    {
        bzero(mes.buf, 100);
        // читаем сообщение с консоли
        fgets(mes.buf, 100, stdin);
        mes.buf[strlen(mes.buf) - 1] = '\0';
        // шлем его серверу
        mes.type = 5L;
        res = msgsnd(queue, (void *)&mes, sizeof(Message), 0);
        if (res != 0)
        {
            printf("Error while sending msg\n");
            exit(1);
        }
        // получаем ответ, что все хорошо
        res = msgrcv(queue, &mes, sizeof(Message), 2L, 0);
        if (res < 0)
        {
            printf("Error while recving msg\n");
            exit(1);
        }
        printf("Server's response: %s\n", mes.buf);
    }
    return 0;
}