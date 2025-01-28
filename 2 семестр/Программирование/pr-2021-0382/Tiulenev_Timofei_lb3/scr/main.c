#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define LEN 5000

int count = 0;

int cmp(const void* a, const void* b){
    const char* aa = *((const char**)a);
    const char* bb = *((const char**)b);
    long int num1 = atol(aa);
    long int num2 = atol(bb);
    if(num1 > num2)
        return 1;
    if(num1 < num2)
        return -1;
    return 0;
}

void check_file(const char *filePath, char** answer){
    FILE *fp = fopen(filePath, "r");

    if(NULL != fgets(answer[count++], LEN, fp))

    fclose(fp);
}

void printDir(const char *dirPath, char** answer){
    char next[LEN] = "";
    strcpy(next, dirPath);
    strcat(next, "/");

    DIR *dir = opendir(dirPath);
    struct dirent* de = readdir(dir);

    if(dir){
        while(de){
            if (de->d_type == DT_REG){
                char file_path[LEN] = "";
                strcat(file_path, next);
                strcat(file_path, de->d_name);
                check_file(file_path, answer);
            }

            if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
                int len = (int)strlen(next);
                strcat(next, de->d_name);
                printDir(next, answer);
                next[len] = '\0';
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
}

int main(){
    char** answer = malloc(sizeof(char*) * LEN);

    for (int i = 0; i < LEN; i++){
        answer[i] = malloc(sizeof(char) * LEN);
        answer[i][0] = '\0';
    }

    printDir("root", answer);

    qsort(answer, count, sizeof(char*), cmp);

    FILE *result = fopen("result.txt", "w");

    for (int i = 0; i < count; i++)
        fprintf(result, "%s\n", answer[i]);

    fclose(result);

    for (int i = 0; i < LEN; i++){
        free(answer[i]);
    }
    free(answer);

    return 0;
}