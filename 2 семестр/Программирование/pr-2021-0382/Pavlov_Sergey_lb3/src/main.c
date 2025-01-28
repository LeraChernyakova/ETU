#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 5000

int count = 0;

int compare(const void *a, const void *b){
    const char *aa = *((const char**)a);
    const char *bb = *((const char**)b);
    long int nmb1 = atol(aa);
    long int nmb2 = atol(bb);

    if(nmb1 > nmb2){
        return 1;
    } else if(nmb1 < nmb2){
        return -1;
    } else {
        return 0;
    }
}

void scanFile(const char *path, char **txt){
    FILE *file = fopen(path, "r");

    if(NULL != fgets(txt[count++],BUF_SIZE/5,file))

    fclose(file);
}

void scanDir(const char *path, char **res){

    char next[BUF_SIZE] = "";
    strcat(next,path);
    strcat(next,"/");

    DIR *dir = opendir(path);
    if(!dir){
        return;
    }

    struct dirent *de = readdir(dir);
    if(dir){
        while(de){
            if(de->d_type == DT_REG){
                char file_path[BUF_SIZE] = "";
                strcat(file_path,next);
                strcat(file_path,de->d_name);
                scanFile(file_path,res);
            }

            if(de->d_type == DT_DIR && strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..") != 0){
                int len = (int)strlen(next);
                strcat(next, de->d_name);
                scanDir(next,res);
                next[len] = '\0';
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
}


int main() {
    char** result = malloc(sizeof(char *) * BUF_SIZE);
    int i;
    for(i=0; i<BUF_SIZE; i++){
        result[i] = malloc(sizeof(char) * (BUF_SIZE/5));
        result[i][0] = '\0';
    }

    scanDir("root", result);
    qsort(result, count, sizeof(char*), compare);
    FILE *res = fopen("result.txt","w");
    for(i = 0; i<count; i++){
        fprintf(res,"%s\n",result[i]);
    }
    fclose(res);

    for(i=0; i<BUF_SIZE; i++){
        free(result[i]);
    }
    free(result);
    return 0;
}
