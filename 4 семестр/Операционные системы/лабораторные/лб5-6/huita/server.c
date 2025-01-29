#include <stdio.h> 
#include <stdlib.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/types.h> 
#include <signal.h> 
#include <unistd.h> 
#include <strings.h> 
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include "shm.h"
int* buf;
int shmemory;
int semaphore;
void intHandler(int sig) {
 shmdt(buf);
 shmctl(shmemory, IPC_RMID, 0);
 semctl(semaphore, 0, IPC_RMID);
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
if((shmemory = shmget(key,(BUF_SIZE+1)*sizeof(int),IPC_CREAT|0666))< 0)
{
 printf("Can't create shm\n");
exit(1);
 }
 //присоединяем shm в наше адресное пространство
 if((buf = (int*)shmat(shmemory, 0, 0)) < 0) {
 printf("Error while attaching shm\n");
 exit(1);
 }
// устанавливаем обработчик сигнала
 signal(SIGINT, intHandler);
 //создаем группу из 3 семафоров
 //1 - число свободных ячеек
 //2 - число занятых ячеек
 // 3 работа с памятью
 if((semaphore = semget(key, 3, IPC_CREAT | 0666)) < 0) {
 printf("Error while creating semaphore\n");
 kill(getpid(),SIGINT);
 }
 // устанавливаем индекс в -1,
//первый записывающий клиент установит его в ноль
 buf[BUF_SIZE] = -1;
 // инициализируем массив -1
 int j = 0;
 for(j = 0; j < BUF_SIZE; ++j) {
 buf[j] = -1;
 }
//устнавливаем 1 семафор в число свободных ячеек,т.е. можно писать
 if(semop(semaphore, setFree, 1) < 0) {
 printf("execution complete\n");
 kill(getpid(),SIGINT);
 }
 // говорим, что память свободна
 if(semop(semaphore, mem_unlock, 1) < 0) {
 printf("execution complete\n");
 kill(getpid(),SIGINT);
 }
 printf("Press enter to start working\n");
 getchar();
// основной цикл работы
int i = 0;
 for(i = 0; i < 15; ++i) {
// ждем, пока будет хоть одна непустая ячейка
 if(semop(semaphore, waitNotEmpty, 1) < 0) {
 printf("execution complete\n");
 kill(getpid(),SIGINT);
 }
 // ждем возможности поработать с памятью
 if(semop(semaphore, mem_lock, 1) < 0) {
 printf("execution complete\n");
 kill(getpid(),SIGINT);
 }

 //читаем сообщение от клиента
 int res = buf[buf[BUF_SIZE]];
 buf[BUF_SIZE] = buf[BUF_SIZE] - 1;
 printf("Remove %d from cell %d\n", res,buf[BUF_SIZE]+1);
 // освобождаем память
 if(semop(semaphore, mem_unlock, 1) < 0) {
 printf("execution complete\n");
 kill(getpid(),SIGINT);
 }
 // увеличиваем число пустых ячеек
 if(semop(semaphore, releaseEmpty, 1) < 0) {
 printf("execution complete\n");
 kill(getpid(),SIGINT);
 }
 }
}