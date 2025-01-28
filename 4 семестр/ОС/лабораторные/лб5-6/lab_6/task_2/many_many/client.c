#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("Usage: ./client <channel1> <channel2>\n");
        exit(1);
    }

    char channel1[10], channel2[10];
    strcpy(channel1, argv[1]);
    strcpy(channel2, argv[2]);

    // открываем каналы
    int chan1 = open(channel1, O_RDONLY);
    if (chan1 == -1) {
        printf("Can't open channel1 for reading\n");
        exit(0);
    }

    int chan2 = open(channel2, O_WRONLY);
    if (chan2 == -1) {
        printf("Can't open channel2 for writing\n");
        exit(0);
    }

    // читаем имя файла из первого канала
        char fileName[100];
    bzero(fileName, 100);
    int res = read(chan1, fileName, 100);
    if (res <= 0) {
        printf("Can't read fileName from channel1\n");
        exit(0);
    }

    // открываем файл на чтение
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printf("Can't open file %s\n", fileName);
        exit(0);
    }

    // читаем из файла и пишем во второй канал
    char buf[100];
    while (!feof(f)) {
        // читаем данные из файла
        res = fread(buf, sizeof(char), 100, f);
        printf("reading message %s\n", buf);
        // пишем их в канал
        write(chan2, buf, res);
        printf("sending message %s\n", buf);
    }

    fclose(f);
    close(chan1);
    close(chan2);

    return 0;
}

