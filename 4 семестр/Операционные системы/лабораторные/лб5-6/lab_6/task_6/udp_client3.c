#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define DEF_PORT 80
#define DEF_IP "15.0.3.1"

int main(int argc, char **argv)
{
    char *addr;
    int port;
    char *readbuf;
    printf("Using default port %d\n", DEF_PORT);
    port = DEF_PORT;
    printf("Using default addr %s\n", DEF_IP);
    addr = DEF_IP;

    struct sockaddr_in peer;
    peer.sin_family = AF_INET; // Используем IPv4
    peer.sin_port = htons(port); // Задаем порт
    peer.sin_addr.s_addr = inet_addr(addr); 

    int sock = socket(AF_INET, SOCK_DGRAM, 0); // Создаем сокет для передачи данных по UDP
    if (sock < 0)
    {
        perror("Can’t create socket\n");
        exit(1);
    }

    char buf[100];
    int first_msg = 1;
    int peer_addr_size = sizeof(peer);

    for (;;)
    {
        printf("Input request (empty to exit)\n");
        if (first_msg == 0){
            bzero(buf, 100);
            fgets(buf, 100, stdin);
            buf[strlen(buf)-1] = '\0';
        }
        else{
        for (int k = 0; k < 10;k++){
        	buf[0] = argv[1][10];
            for (int i = 1; i < 90; i++){
                char j = i%10 + '0';
                buf[i] = j;
            buf[strlen(buf)] = '\0';
            first_msg = 0;
            if (strlen(buf) == 0)
            {
                printf("Bye-bye\n");
                return 0;
            }
            // Отправляем запрос на сервер
            int res = sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&peer, sizeof(peer));
            if (res <= 0)
            {
                perror("Error while sending:");
                exit(1);
            }
            }
            bzero(buf, 100);
           }
            
            //strcpy(buf, argv[1]);
            //buf[strlen(buf)] = '\0';
            //first_msg = 0;
        }
        if (strlen(buf) == 0)
        {
            printf("Bye-bye\n");
            return 0;
        }
        // Отправляем запрос на сервер
        int res = sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&peer, sizeof(peer));
        if (res <= 0)
        {
            perror("Error while sending:");
            exit(1);
        }
        bzero(buf, 100);
        // Получаем ответ от сервера.
        res = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr *)&peer, &peer_addr_size);
        if (res <= 0)
        {
            perror("Error while receiving:");
            exit(1);
        }

        printf("Server’s response: %s\n", buf);
    }
    return 0;
}
