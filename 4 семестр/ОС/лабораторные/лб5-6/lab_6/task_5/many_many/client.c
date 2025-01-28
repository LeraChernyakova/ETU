#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEF_PORT 8888
#define DEF_IP "127.0.0.1"

int main(int argc, char **argv) {
    char *addr;
    int port;
    printf("Using default port %d\n", DEF_PORT);
    port = DEF_PORT;
    printf("Using default addr %s\n", DEF_IP);
    addr = DEF_IP;

    if (argc > 2) {
        addr = argv[1];
        port = atoi(argv[2]);
        printf("Using addr %s\n", addr);
        printf("Using port %d\n", port);
    }

    struct sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(port);
    peer.sin_addr.s_addr = inet_addr(addr);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Can't create socket\n");
        exit(1);
    }

    int res = connect(sock, (struct sockaddr *)&peer, sizeof(peer));
    if (res) {
        perror("Can't connect to server:");
        exit(1);
    }

    // основной цикл программы
    char buf[100];
    int first_msg = 1;
    for (;;) {
        printf("Input request (empty to exit)\n");
        if (first_msg == 0){
            bzero(buf, 100);
            fgets(buf, 100, stdin);
            buf[strlen(buf) - 1] = '\0';
        }
        else{
            strcpy(buf, argv[3]);
            buf[strlen(buf)] = '\0';
            first_msg = 0;
        }
        if (strlen(buf) == 0) {
            printf("Bye-bye\n");
            return 0;
        }

        res = sendFix(sock, buf, 0);
        if (res <= 0) {
            perror("Error while sending:");
            exit(1);
        }

        bzero(buf, 100);
        res = readFix(sock, buf, 100, 0);
        if (res <= 0) {
            perror("Error while receiving:");
            exit(1);
        }
        printf("Server's response: %s\n", buf);
    }
    return 0;
}

int readFix(int sock, char *buf, int bufSize, int flags) {
    unsigned msgLength = 0;
    int res = recv(sock, &msgLength, sizeof(unsigned), flags | MSG_WAITALL);
    if (res <= 0) return res;
    if (res > bufSize) {
        printf("Received more data than we can store, exiting\n");
        exit(1);
    }
    return recv(sock, buf, msgLength, flags | MSG_WAITALL);
}

int sendFix(int sock, char *buf, int flags) {
    unsigned msgLength = strlen(buf);
    int res = send(sock, &msgLength, sizeof(unsigned), flags);
    if (res <= 0) return res;
    return send(sock, buf, msgLength, flags);
}

