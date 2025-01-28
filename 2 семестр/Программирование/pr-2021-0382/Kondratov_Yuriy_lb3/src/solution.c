#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

#define MAX_I_SIZE 128
#define MAX_PATH_SIZE 512 


void get_file_path(char *file_name, char *dir_name, char *path){

    DIR *dir = opendir(dir_name);
    if (!dir) return;

    struct dirent *cur_elem = readdir(dir); 
    while (cur_elem){
        if (cur_elem->d_type == DT_REG){
            if (!strcmp(cur_elem->d_name, file_name)){
                strcpy(path, "./");
                strcat(path, dir_name);
                strcat(path, "/");
                strcat(path, file_name);
                return;
            } 
        }
        if (cur_elem->d_type == DT_DIR &&
             strcmp(cur_elem->d_name, ".") &&
             strcmp(cur_elem->d_name, "..")) {
            char new_dir[strlen(dir_name) + strlen(cur_elem->d_name) + 2];
            new_dir[0] = '\0';
            strcat(new_dir, dir_name);
            strcat(new_dir, "/");
            strcat(new_dir, cur_elem->d_name);
            get_file_path(file_name, new_dir, path);
        }
        cur_elem = readdir(dir);
    }
    closedir(dir);
}

int main() {
    char *dir_name = "tmp";
    char input[MAX_I_SIZE];
    fgets(input, MAX_I_SIZE, stdin);
    input[strlen(input) - 1] = '\0';

    FILE *result = fopen("result.txt", "w");
    char file_name[] = {' ', '.', 't', 'x', 't', '\0'};
    for (int i = 0; i < strlen(input); i++){
        char path[MAX_PATH_SIZE];
        file_name[0] = input[i];
        get_file_path(file_name, dir_name, path);
        strcat(path, "\n");
        fputs(path, result);
    }
    fclose(result);
    return 0;
}
