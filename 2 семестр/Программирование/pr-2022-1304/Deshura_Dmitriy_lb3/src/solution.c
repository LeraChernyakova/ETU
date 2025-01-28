#include <stdio.h>
#include "dirent.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"


int multiplicator (int start, char* path);


int sumator(int start, char* path) {
    int res = start;
    DIR *dir = opendir(path);
    if (dir) {
        struct dirent *curdir = readdir(dir);
        while (curdir) {
            if (!strcmp(curdir -> d_name, "add")) {
                strcat(path, "/add");
                res += sumator(0, path);
                path[strlen(path) - 4] = '\0';
            } else {
                if (!strcmp(curdir -> d_name, "mul")) {
                    strcat(path, "/mul");
                    res += multiplicator(1, path);
                    path[strlen(path) - 4] = '\0';
                } else {
                    if(curdir -> d_type == DT_REG){
                        char* buf, str[100];
                        strcat(strcat(path, "/"), curdir -> d_name);
                        FILE *file = fopen(path, "r");
                        fgets(str, 100, file);

                        buf = strtok(str, " ");
                        while (buf) {
                            res += atoi(buf);
                            buf = strtok(NULL, " ");
                        }
                        fclose(file);
                        path[strlen(path) - strlen(curdir -> d_name) - 1] = '\0';
                    }
                }
            }
            
            curdir = readdir(dir);
        }
        closedir (dir);
    }

    return res;
}


int multiplicator (int start, char* path) {
    int res = start;
    DIR *dir = opendir(path);
    if (dir) {
        struct dirent *curdir = readdir(dir);
        while (curdir) {
            if (!strcmp(curdir -> d_name, "add")) {
                strcat(path, "/add");
                res *= sumator(0, path);
                path[strlen(path) - 4] = '\0';
            } else {
                if (!strcmp(curdir -> d_name, "mul")) {
                    strcat(path, "/mul");
                    res *= multiplicator(1, path);
                    path[strlen(path) - 4] = '\0';
                } else {
                    if (curdir -> d_type == DT_REG) {
                        char* buf, str[100];
                        strcat(strcat(path, "/"), curdir -> d_name);
                        FILE *file = fopen(path, "r");
                        fgets(str, 100, file);

                        buf = strtok(str, " ");
                        while (buf) {
                            res *= atoi(buf);
                            buf = strtok(NULL, " ");
                        }
                        fclose(file);
                        path[strlen(path) - strlen(curdir -> d_name) - 1] = '\0';
                    }
                }
            }
            
            curdir = readdir(dir);
        }
        closedir (dir);
    }

    return res;
}


int main() {
    char path[256] = "tmp";
    long long int res;
    DIR *dir = opendir(path);
    struct dirent *directory = readdir(dir);
    while(directory){
        if(!strcmp(directory -> d_name, "add")){
            strcat(path, "/add");
            res = sumator(0, path);
            break;
        }
        if(!strcmp(directory -> d_name, "mul")){
            strcat(path, "/mul");
            res = multiplicator(1, path);
            break;
        }
        directory = readdir(dir);
    }
    closedir (dir);

    FILE *file = fopen("result.txt", "w");
    fprintf(file, "%lld\n", res);
    fclose(file);
    return 0;
}