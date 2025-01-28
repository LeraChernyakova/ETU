#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define BUF 10000

int count = 0;

int cmp(const void* a, const void* b){
    const char* aa = *((const char**)a);
    const char* bb = *((const char**)b);
    long int num1 = atol(aa);
    long int num2 = atol(bb);
    if(num1 > num2){
        return 1;
    }
    else if(num1 < num2){
        return -1;
    }
    else return 0;
}

void check(const char *path, char** text){
    FILE *fp = fopen(path, "r");

    if(NULL != fgets(text[count++], BUF, fp))

    fclose(fp);
}

void print(const char *dirPath, char** text){
    char next[BUF] = "";
    strcpy(next, dirPath);
    strcat(next, "/");

    DIR *dir = opendir(dirPath);
    struct dirent* de = readdir(dir);

    if(dir){
        while(de){
            if (de->d_type == DT_REG){
                char file_path[BUF] = "";
                strcat(file_path, next);
                strcat(file_path, de->d_name);
                check(file_path, text);
            }

            if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
                int len = (int)strlen(next);
                strcat(next, de->d_name);
                print(next, text);
                next[len] = '\0';
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
}

int main(){
    char** text = malloc(sizeof(char*) * BUF);
    int i;
    
    for (i = 0; i < BUF; i++){
        text[i] = malloc(sizeof(char) * BUF);
        text[i][0] = '\0';
    }

    print("root", text);
    qsort(text, count, sizeof(char*), cmp);
    FILE *result = fopen("result.txt", "w");

    for (i = 0; i < count; i++){
        fprintf(result, "%s\n", text[i]);
    }
    
    fclose(result);

    for (i = 0; i < BUF; i++){
        free(text[i]);
    }
    free(text);

    return 0;
}
