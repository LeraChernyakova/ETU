#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

long long int makeOperations(char *path, char *last_dir){
    printf("%s\n", path);
    long long int tmp, res = 0;
    char *dir_copy;
    DIR *dir = opendir(path);
    if(!strcmp(last_dir, "add")){
        res = 0;
        struct dirent *cur = readdir(dir);
        while(cur){
            if(strcmp(cur->d_name, "add") == 0){
                dir_copy = (char *)calloc(strlen(path) + 5, sizeof(char));
                strcpy(dir_copy, path);
                strcat(dir_copy, "/add");
                res += makeOperations(dir_copy, "add");
                free(dir_copy);
            }
            else if(strcmp(cur->d_name, "mul") == 0){
                dir_copy = (char *)calloc(strlen(path) + 5, sizeof(char));
                strcpy(dir_copy, path);
                strcat(dir_copy, "/mul");
                res += makeOperations(dir_copy, "mul");
                free(dir_copy);
            }
            else if(strstr(cur->d_name, ".txt") != NULL){
                dir_copy = (char *)calloc(strlen(path) + strlen(cur->d_name) + 2, sizeof(char));
                strcpy(dir_copy, path);
                strcat(dir_copy, "/");
                strcat(dir_copy, cur->d_name);
                FILE *file = fopen(dir_copy, "r");
                while(fscanf(file, "%lld", &tmp) != EOF){
                    res += tmp;
                }
                fclose(file);
                free(dir_copy);
            }
            cur = readdir(dir);
        }
    }
    else if(!strcmp(last_dir, "mul")){
        res = 1;
        struct dirent *cur = readdir(dir);
        while(cur){
                if(strcmp(cur->d_name, "add") == 0){
                dir_copy = (char *)calloc(strlen(path) + 5, sizeof(char));
                strcpy(dir_copy, path);
                strcat(dir_copy, "/add");
                res *= makeOperations(dir_copy, "add");
                free(dir_copy);
            }
            else if(strcmp(cur->d_name, "mul") == 0){
                dir_copy = (char *)calloc(strlen(path) + 5, sizeof(char));
                strcpy(dir_copy, path);
                strcat(dir_copy, "/mul");
                res *= makeOperations(dir_copy, "mul");
                free(dir_copy);
            }
            else if(strstr(cur->d_name, ".txt") != NULL){
                dir_copy = (char *)calloc(strlen(path) + strlen(cur->d_name) + 2, sizeof(char));
                strcpy(dir_copy, path);
                strcat(dir_copy, "/");
                strcat(dir_copy, cur->d_name);
                FILE *file = fopen(dir_copy, "r");
                while(fscanf(file, "%lld", &tmp) != EOF){
                    res *= tmp;
                }
                fclose(file);
                free(dir_copy);
            }
            cur = readdir(dir);
        }
    }
    else if(!strcmp(last_dir, "tmp")){
        res = 0;
        struct dirent *cur = readdir(dir);
        while(cur){
            if(strcmp(cur->d_name, "add") == 0){
                dir_copy = (char *)calloc(strlen(path) + 5, sizeof(char));
                strcpy(dir_copy, path);
                strcat(dir_copy, "/add");
                res += makeOperations(dir_copy, "add");
                free(dir_copy);
            }
            else if(strcmp(cur->d_name, "mul") == 0){
                dir_copy = (char *)calloc(strlen(path) + 5, sizeof(char));
                strcpy(dir_copy, path);
                strcat(dir_copy, "/mul");
                res += makeOperations(dir_copy, "mul");
                free(dir_copy);
            }
            cur = readdir(dir);
        }
    }
    return res;
}

int main(int argc, char **argv){
    char *path = (char *)calloc(4, sizeof(char));
    long long int res = 0;
    FILE *resultf = fopen("result.txt", "w");
    strcpy(path, "tmp");
    res = makeOperations(path, path);
    fprintf(resultf, "%lld", res);
    fclose(resultf);
    return 0;
}