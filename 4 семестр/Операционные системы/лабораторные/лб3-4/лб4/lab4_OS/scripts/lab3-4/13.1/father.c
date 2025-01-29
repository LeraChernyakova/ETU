#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int defaultExample(){
    int wstatus;
    pid_t c_pid = fork();
    if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (c_pid == 0) {
	printf("printed from child proc\n");
   	execl("son1", "son1", NULL);    
    } else {
        printf("printed from parent process - %d\n", getpid());
        int ret;
	sleep(1);
	system("echo >> file.txt");
        system("echo After 1st child: >> file.txt");
        system("ps -s >> file.txt");
        ret = kill(c_pid, SIGTERM);
        if (ret == -1) {
            perror("kill");
            exit(EXIT_FAILURE);
        }
        if (waitpid(c_pid, &wstatus, WUNTRACED | WCONTINUED) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
	else{
	    puts("son1 exited sucessfuly\n");
	}
    }
    return 0; 
}

int ignoreSignalExample(){
    int wstatus;
    pid_t c_pid = fork();
    if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (c_pid == 0) {
        printf("printed from child proc\n");
        execl("son2", "son2", NULL);
    } else {
        printf("printed from parent process - %d\n", getpid());
        int ret;
        sleep(1);
	system("echo >> file.txt");
        system("echo After 2nd child: >> file.txt");
        system("ps -s >> file.txt");
        ret = kill(c_pid, SIGTERM);
        if (ret == -1) {
            perror("kill");
            exit(EXIT_FAILURE);
        }
        if (waitpid(c_pid, &wstatus, WUNTRACED | WCONTINUED) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        else{
            puts("son2 exited sucessfuly\n");
        }
    }
    return 0;
}

int interceptSignalExample(){
    int wstatus;
    pid_t c_pid = fork();
    if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (c_pid == 0) {
        printf("printed from child proc\n");
        execl("son3", "son3", NULL);
    } else {
        printf("printed from parent process - %d\n", getpid());
        int ret;
        sleep(1);
	system("echo >> file.txt");
	system("echo After 3rd child: >> file.txt");
	system("ps -s >> file.txt");
        ret = kill(c_pid, SIGTERM);
        if (ret == -1) {
            perror("kill");
            exit(EXIT_FAILURE);
        }
        if (waitpid(c_pid, &wstatus, WUNTRACED | WCONTINUED) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        else{
            puts("son3 exited sucessfuly\n");
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    system("echo Before: >> file.txt");
    system("ps -s >> file.txt");
    return defaultExample() + ignoreSignalExample() + interceptSignalExample();
}