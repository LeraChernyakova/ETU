#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>

typedef struct searchLink
{
    char** letter;
    char** path;
    int n;
} searchLink;

void listDir(const char* path, searchLink* ex)
{
    char next[200]={0};
    strcpy(next,path);
    strcat(next,"/");
    DIR* dir = opendir(path);
    if (!dir)
        return;
    struct dirent* de=readdir(dir);
    while (de)
    {
        for (int i=0;i<ex->n;i++)
        {
            if (strcmp(de->d_name,ex->letter[i])==0)
            {
                ex->path[i]=calloc(100,sizeof(char));
                strcpy(ex->path[i],next);
                strcat(ex->path[i],ex->letter[i]);
                break;
            }
        }
        if (de->d_type == DT_DIR && strcmp(de->d_name, ".")!=0 && strcmp(de->d_name, "..")!=0)
        {
            int len=strlen(next);
            strcat(next,de->d_name);
            listDir(next,ex);
            next[len]='\0';
        }
        de=readdir(dir);
    }
    closedir(dir);
}

void createOutput(char* filename,searchLink* ex)
{
    FILE* f= fopen(filename,"w");
    for (int i=0;i<ex->n;i++)
    {
        fprintf(f,"%s\n",ex->path[i]);
    }
    fclose(f);
}

int main()
{
    char* str=calloc(100,sizeof(char));
    fgets(str,100,stdin);
    searchLink ex;
    ex.n= strlen(str)-1;
    ex.letter= calloc(strlen(str),sizeof(char*));
    ex.path= calloc(strlen(str),sizeof(char*));
    for (int i=0;i<strlen(str)-1;i++)
    {
        ex.letter[i]=calloc(100,sizeof(char));
        ex.letter[i][0]=str[i];
        strcat(ex.letter[i],".txt\0");
    }
    listDir("./tmp",&ex);
    createOutput("result.txt",&ex);
    return 0;
}
