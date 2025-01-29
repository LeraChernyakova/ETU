#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUM_CHILDREN 3

int main() {
    int i, res;
    char buf[100];
    int filedes[2*NUM_CHILDREN];

    for (i = 0; i < NUM_CHILDREN; i++) {
        if (pipe(filedes + i*2) < 0) {
            perror("Can't create pipe");
            exit(1);
        }

        if (fork() == 0) { // Child process
            close(filedes[i*2]); // Close reading end

            // Assume each child reads from a different file
            // Replace "ChildFileX.txt" with the actual file name
            char childFileName[16];
            sprintf(childFileName, "ChildFile%d.txt", i+1);
            FILE* f = fopen(childFileName, "r");
            if (!f) {
                perror("Can't open child file");
                exit(1);
            }

            while (!feof(f)) {
                res = fread(buf, sizeof(char), 100, f);
                write(filedes[i*2+1], buf, res); // Write to pipe
            }

            fclose(f);
            close(filedes[i*2+1]);
            exit(0);
        }

        // Parent process
        close(filedes[i*2+1]); // Close writing end
    }

    // Parent reads from the pipes and writes to its file
    // Replace "ParentFile.txt" with the actual file name
    FILE* f = fopen("ParentFile.txt", "w");
    if (!f) {
        perror("Can't open parent file");
        exit(1);
    }

    for (i = 0; i < NUM_CHILDREN; i++) {
        while (1) {
            bzero(buf, 100);
            res = read(filedes[i*2], buf, 100);
            if (!res)
                break;
            fwrite(buf, sizeof(char), res, f);
        }
        close(filedes[i*2]);
    }

    fclose(f);
    return 0;
}