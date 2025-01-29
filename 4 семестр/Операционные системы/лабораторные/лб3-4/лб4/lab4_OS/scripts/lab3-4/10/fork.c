#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i, j;
    
    for (i = 0; i < 2; ++i) {
        pid_t pid = fork();
        
        if (pid == 0) {
            printf("Child %d with parent %d\n", getpid(), getppid());
            
            for (j = 0; j < 2; ++j) {
                pid_t pid2 = fork();
                
                if (pid2 == 0) {
                    printf("\tSub Child %d with parent %d\n", getpid(), getppid());
                    break;
                } else if (pid2 == -1) {
                    printf("Error: Failed to create sub child\n");
                    return 1;
                } else {
                    // Parent process of sub child
                    wait(NULL);
                }
            }
            
            break;
        } else if (pid == -1) {
            printf("Error: Failed to create child\n");
            return 1;
        } else {
            // Parent process
            wait(NULL);
        }
    }
    
    return 0;
}
