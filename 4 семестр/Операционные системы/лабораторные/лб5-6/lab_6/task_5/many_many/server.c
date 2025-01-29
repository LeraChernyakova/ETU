#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define DEF_PORT 8888

void *clientHandler(void *args)
{
    int sock = (int)args;
    char buf[100];
    int res = 0;
    for (;;)
    {
        bzero(buf, 100);
        res = readFix(sock, buf, 100, 0);
        if (res <= 0)
        {
            perror("Can't recv data from client, ending thread\n");
            pthread_exit(NULL);
        }
        printf("Some client sent: %s\n", buf);
        res = sendFix(sock, buf, 0);
        if (res <= 0)
        {
            perror("send call failed");
            pthread_exit(NULL);
        }
    }
}

int main(int argc, char **argv){
    int port = 0;
    if (argc < 2){
        printf("Using default port %d\n", DEF_PORT);
        port = DEF_PORT;}
    else
        port = atoi(argv[1]);

    struct sockaddr_in listenerInfo;
    listenerInfo.sin_family = AF_INET;
    listenerInfo.sin_port = htons(port);
    listenerInfo.sin_addr.s_addr = htonl(INADDR_ANY);

    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        perror("Can't create socket to listen: ");
        exit(1);
    }

    int res = bind(listener, (struct sockaddr *)&listenerInfo, sizeof(listenerInfo));
    if (res < 0)
    {
        perror("Can't bind socket");
        exit(1);
    }

    res = listen(listener, 5);
    if (res)
    {
        perror("Error while listening:");
        exit(1);
    }

    for (;;){
        int client = accept(listener, NULL, NULL);
        pthread_t thrd;
        res = pthread_create(&thrd, NULL, clientHandler, (void *)(client));
        if (res)
        {
            printf("Error while creating new thread\n");}}
    return 0;
}

int readFix(int sock, char *buf, int bufSize, int flags){
    unsigned msgLength = 0;
    int res = recv(sock, &msgLength, sizeof(unsigned), flags | MSG_WAITALL);
    if (res <= 0)
        return res;
    if (res > bufSize){
        printf("Received more data than we can store, exiting\n");
        exit(1);}
    return recv(sock, buf, msgLength, flags | MSG_WAITALL);}

int sendFix(int sock, char *buf, int flags){
    unsigned msgLength = strlen(buf);
    int res = send(sock, &msgLength, sizeof(unsigned), flags);
    if (res <= 0)
        return res;
    return send(sock, buf, msgLength, flags);}

