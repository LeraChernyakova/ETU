#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int calculate(char* path, char* dir_name){
    char* newPath;
    if(!strcmp(dir_name, "")) newPath = path;
    else{
        newPath = malloc((strlen(path) + strlen(dir_name) + 10)*sizeof(char));
        sprintf(newPath, "%s/%s", path, dir_name);
    }

    DIR* D = opendir(newPath);
    struct dirent* dir;

    int result = strcmp(dir_name, "add") ? 1 : 0;

    while((dir = readdir(D)) != NULL){
        if(dir->d_type & DT_DIR){
            if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")){
                if(!strcmp(dir_name, "add")) result += calculate(newPath, dir->d_name);
                else result *= calculate(newPath, dir->d_name);
            }
        }
        else{
            char* filePath = malloc((strlen(newPath) + strlen(dir->d_name) + 10)*sizeof(char));
            sprintf(filePath, "%s/%s", newPath, dir->d_name);
            FILE* stream = fopen(filePath, "r");

            int i ;
            while(!feof(stream)){
                fscanf(stream, "%d", &i);
                if(!strcmp(dir_name, "add")) result += i;
                else result *= i; 
            }
            free(filePath);
            fclose(stream);
        } 
    }
    if(strcmp(dir_name, "")) free(newPath);
    closedir(D);
    return result;
}

int main() {
    FILE* result = fopen("./result.txt", "w");
    fprintf(result, "%ld", calculate("./tmp", ""));
    fclose(result);
    return 0;
}