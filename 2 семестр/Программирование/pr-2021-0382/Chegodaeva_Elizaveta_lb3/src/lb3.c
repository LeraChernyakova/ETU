#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define N 100

void PrintWay(char str, FILE *res, const char *path){
    DIR *dir = opendir(path);
    if (!dir){
        return;
    }
    char *way_p=calloc(N, sizeof(char));
    struct dirent* de = readdir(dir);
    while(de){
    	strcpy(way_p, path);
    	strcat(way_p, "/");
        if ((de->d_type==DT_REG) && (de->d_name[0]==str)  && (de->d_name[1]=='.')){
            fprintf(res,"%s/%s\n",path, de->d_name);
        }
        if ((de->d_type==DT_DIR) && (strcmp(de->d_name, ".")!=0) && (strcmp(de->d_name, "..")!=0)){
            strcat(way_p, de->d_name);
            PrintWay(str, res, way_p);
        }
        de = readdir(dir);
    }
    closedir(dir);
    free(way_p);
}

int main(){
    int i=0;
    char str[N];
    fgets(str, N, stdin);
    FILE *result = fopen("result.txt", "w");
    char* way;
    way = "./tmp";
    for (i=0; i<strlen(str); i++){
        PrintWay(str[i], result, way);
    }
    fclose(result);
    return 0;
}


