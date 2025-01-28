#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int takePath(char *labirint, char** names, char** ways, int* count){
    char tway[PATH_MAX + 1];
    DIR *dir = NULL;
    struct dirent *indir = NULL;
    dir = opendir(labirint);
    if(dir==NULL){ return -1;}
    indir=readdir(dir);
    while(indir != NULL){
        struct stat inf;
        if((strncmp( indir->d_name, ".", PATH_MAX) == 0) || (strncmp( indir->d_name, "..", PATH_MAX) == 0)){
            indir = readdir(dir);
            continue;
        }
        strncpy(tway, labirint, PATH_MAX);
        strncat(tway, "/", PATH_MAX);
        strncat(tway, indir->d_name, PATH_MAX);
        if(lstat(tway, &inf)== 0){
            if(S_ISDIR(inf.st_mode)){
                takePath(tway, names, ways, count);
            }
            else
            if(S_ISREG(inf.st_mode)){
                names[*count] = malloc(300*sizeof(char));
                (names[*count])[0]='\0';
                ways[*count] = malloc(300*sizeof(char));
                (ways[*count])[0]='\0';

                strcat(names[*count], indir->d_name);
                strcat(ways[*count], labirint);

                (*count)+=1;
            }
        }
        indir=readdir( dir );
    }

    closedir(dir);
    return 0;
}

int minotavr(char* name, char** names, char** ways, int count, char** result, int* _count){
    int i;
    for(i=0; i<count;i++)
        if (strcmp(names[i], name)==0)
            break;
    char* way[300];
    way[0]='\0';
    strcat(way, ways[i]);
    strcat(way, "/");
    strcat(way, names[i]);

    FILE * file = fopen(way, "r");
    char str[300];
    str[0]='\0';
    char fname[300];
    char a[]="Minotaur";
    char b[]="Deadlock";
    char c[]="@include";
    fname[0]='\0';

    while(fscanf(file, "%s", str) != EOF){
        if(strcmp(str, c)==0){
            fscanf(file, "%s\n", fname);
            if (minotavr(fname, names, ways, count, result, _count)){
                result[*_count] = malloc(300*sizeof(char));
                (result[*_count])[0] = '\0';
                strcat(result[*_count], way);
                (*_count)++;
                fclose (file);
                return 1;
            }
        }
        else
        if(strcmp(str, a)==0){
            result[*_count] = malloc(300*sizeof(char));
            (result[*_count])[0] = '\0';
            strcat(result[*_count], way);
            (*_count)++;
            fclose (file);
            return 1;
        }
        else
        if(strcmp(str, b)==0){
            fclose (file);
            return 0;
        }
    }
    fclose (file);
    return 0;
}

int main(){
    char* names[5000];
    char* ways[5000];
    char* result[5000];
    char root[]="./labyrinth";
    char res[]="result.txt";
    int count=0;
    int tcount = 0;

    if (takePath( root, names, ways, &count) == 0)
        minotavr("file.txt", names, ways, count, result, &tcount);
    FILE * file = fopen(res, "w");
    while(tcount!=0){
        fputs(result[tcount-1], file);
        fputs("\n", file);
        printf("%s\n",result[tcount-1]);
        tcount--;
    }
    fclose (file);
    return 0;
}
