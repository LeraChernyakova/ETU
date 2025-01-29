#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEF_FILENAME "testFile.txt"

int main(int argc, char** argv) {
    char fileName[30];
    char channel1[10], channel2[10];

    if(argc < 4) {
        printf("Usage: ./server <filename> <channel1> <channel2>\n");
        exit(1);
    }

    strcpy(fileName, argv[1]);
    strcpy(channel1, argv[2]);
    strcpy(channel2, argv[3]);

    // создаем два канала
    int res = mknod(channel1, S_IFIFO | 0666, 0);
    if(res) {
        perror("Can't create first channel");
        exit(1);
    }
    res = mknod(channel2, S_IFIFO | 0666, 0);
    if(res) {
        printf("Can't create second channel\n");
        exit(1);
    }

    // открываем первый канал для записи
    int chan1 = open(channel1, O_WRONLY);
    if(chan1 == -1) {
        printf("Can't open channel for writing\n");
        exit(0);
    }

    // открываем второй канал для чтения
    int chan2 = open(channel2, O_RDONLY);
    if(chan2 == -1) {
        printf("Can't open channel for reading\n");
        exit(0);
    }

    // пишем имя файла в первый канал
    write(chan1, fileName, strlen(fileName));

    // читаем содержимое файла из второго канала
    char buf [100];
    for(;;) {
        bzero(buf, 100);
        res = read(chan2, buf, 100);
        if(res <= 0)
            break;
        printf("Part of file: %s\n", buf);
    }

    close(chan1);
    close(chan2);
    unlink(channel1);
    unlink(channel2);

    return 0;
}

