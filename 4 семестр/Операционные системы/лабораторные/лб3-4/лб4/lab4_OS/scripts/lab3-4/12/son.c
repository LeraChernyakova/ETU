#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    if (mlockall((MCL_CURRENT | MCL_FUTURE)) < 0)
        perror("mlockall error");
    char c;
    int pid, ppid, buf;
    int fdrd = atoi(argv[1]);
    int fdwr = atoi(argv[2]);
    pid = getpid();
    ppid = getppid();
    printf("son file decriptor = %d\n", fdrd);
    printf("son params: pid=%i ppid=%i\n", pid, ppid);
    system("ps -xf -o uid,gid,ruid,pid,ppid,pgid,tty,vsz,stat,command > outp.txt"); 
    sleep(5);
    for (;;)
    {
        if (read(fdrd, &c, 1) != 1)
            return 0;
        write(fdwr, &c, 1);
        printf("pid = %d: %c\n", pid, c);
    }
    return 0;
}
