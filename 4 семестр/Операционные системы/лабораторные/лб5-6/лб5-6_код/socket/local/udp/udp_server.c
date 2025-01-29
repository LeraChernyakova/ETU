#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// Задаем порт и адрес по умолчанию
#define DEF_PORT 8888
#define DEF_IP "127.0.0.1"

int main(int argc, char **argv)
{
    int port = 0;
    
    if (argc < 2)
    {
        printf("Using default port %d\n", DEF_PORT);
        port = DEF_PORT;
    }
    else
        port = atoi(argv[1]); 
        
    struct sockaddr_in listenerInfo;
    // Задаем параметры для создания сокета
    listenerInfo.sin_family = AF_INET; // Используем IPv4
    listenerInfo.sin_port = htons(port); // Задаем порт
    listenerInfo.sin_addr.s_addr = htonl(INADDR_ANY); // Bсе локальные интерфейсы будут слушать этот сокет

    int listener = socket(AF_INET, SOCK_DGRAM, 0); // Создаем сокет для передачи данных по UDP
    if (listener < 0) // Проверяем успешность создания сокета
    {
        perror("Can’t create socket to listen: "); 
        exit(1); 
    }

    int res = bind(listener, (struct sockaddr *)&listenerInfo, sizeof(listenerInfo));
    // Связываем сокет с адресом и портом
    if (res < 0) // Проверяем успешность связывания порта и сокета
    {
        perror("Can’t bind socket"); 
        exit(1); 
    }

    char buf[100];
    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);

    for (;;) // Запускаем бесконечный цикл для получения и отправки сообщений
    {
        bzero(buf, 100); // Обнуляем буфер
        res = recvfrom(listener, buf, sizeof(buf)-1, 0, (struct sockaddr *)&client_addr, &client_addr_size);
        // Принимаем сообщение от клиента и сохраняем данные в буфере
        if (res <= 0) // Проверяем успешность получения сообщения от клиента
        {
            perror("Can’t recv data from client"); 
            exit(1); 
        }
        printf("Some client sent: %s\n", buf); // Выводим сообщение полученное от клиента
        res = sendto(listener, buf, strlen(buf), 0, (struct sockaddr *)&client_addr, client_addr_size);
        // Отправляем сообщение обратно клиенту
        if (res <= 0) // Проверяем успешность отправки сообщения клиенту
        {
            perror("send call failed"); 
            exit(1); 
        }
    }
    return 0;
}
