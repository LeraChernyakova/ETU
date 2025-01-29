#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>  

#define SHARED_MEMORY_OBJECT_NAME "my_shared_memory"
#define SHARED_MEMORY_OBJECT_SIZE 50
#define SHM_CREATE 1
#define SHM_PRINT  3
#define SHM_CLOSE  4

int main()
{
    struct sched_param shdprm; // Значения параметров планирования
    int i, pid;
    pid = getpid();
    int k=0;
    int schedule = sched_getscheduler(0);
    int shm, len, mode = 0;
    char *addr;
    char *name = pid + '0';
    len = strlen(argv[2]);
    len = (len<=SHARED_MEMORY_OBJECT_SIZE)?len:SHARED_MEMORY_OBJECT_SIZE;
    mode = O_CREAT;
    shm = shm_open(SHARED_MEMORY_OBJECT_NAME, mode|O_RDWR, 0777);
    addr = mmap(0, SHARED_MEMORY_OBJECT_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
    memcpy(addr, name, len);
    addr[len] = '\0';
    switch (schedule)
    {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            //    sleep(1);
            break;
        case SCHED_RR:
            //printf("SCHED_RR\n");
            //sleep(5);
            for (int i =0;i<100000000;i++){
                k+=1;
                printf("%s\n", addr);
                sleep(1);
            }
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        case -1:
            perror("SCHED_GETSCHEDULER");
            break;
        default:
            printf("Неизвестная политика планирования\n");
    }
    munmap(addr, SHARED_MEMORY_OBJECT_SIZE);
    close(shm);
    shm_unlink(SHARED_MEMORY_OBJECT_NAME);
    return 0;
}
