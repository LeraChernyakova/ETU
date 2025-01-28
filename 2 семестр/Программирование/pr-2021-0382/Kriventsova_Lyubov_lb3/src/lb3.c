#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int find_minotaur(char* name, char** names, char** ways, int counter, char** result, int* recount)
{
    int i;
    for(i=0; i<counter;i++)
    {
        if (strcmp(names[i], name)==0)
            break;
    }
    char* needway = malloc(260*sizeof(char));
    needway[0]='\0';
    strcat(needway, ways[i]);
    strcat(needway, "/");
    strcat(needway, names[i]);

    FILE * xfile = fopen(needway, "r");
    char* str = malloc(260*sizeof(char));
    str[0]='\0';
    char* xname = malloc(260*sizeof(char));
    xname[0]='\0';

    while(fscanf(xfile, "%s", str) != EOF)
    {
        if(strcmp(str, "@include")==0)
        {
            fscanf(xfile, "%s\n", xname);
            if (find_minotaur(xname, names, ways, counter, result, recount))
            {
                result[*recount] = malloc(256*sizeof(char));
                (result[*recount])[0] = '\0';
                strcat(result[*recount], needway);
                (*recount)++;
                fclose (xfile);
                return 1;
            }
        }
        else if(strcmp(str, "Deadlock")==0)
        {
            fclose (xfile);
            return 0;
        }
        else if(strcmp(str, "Minotaur")==0)
        {
            result[*recount] = malloc(260*sizeof(char));
            (result[*recount])[0] = '\0';
            strcat(result[*recount], needway);
            (*recount)++;
            fclose (xfile);
            return 1;
        }
    }
    fclose (xfile);
    return 0;
}

int gointolab( char *lab, char** names, char** ways, int* counter)
{
    DIR *dir = NULL;
    struct dirent *de = NULL;
    char wayname[PATH_MAX + 1];
    dir = opendir(lab);
    if(dir==NULL) return -1;
    de=readdir(dir);
    while(de != NULL)
    {
        struct stat entryInfo;
        if((strncmp( de->d_name, ".", PATH_MAX) == 0) || (strncmp( de->d_name, "..", PATH_MAX) == 0))
        {
            de = readdir(dir);
            continue;
        }
        (void)strncpy(wayname, lab, PATH_MAX);
        (void)strncat(wayname, "/", PATH_MAX);
        (void)strncat(wayname, de->d_name, PATH_MAX);
        if(lstat(wayname, &entryInfo)== 0)
        {  if(S_ISDIR(entryInfo.st_mode))
            {
                gointolab(wayname, names, ways, counter);
            }
            else if(S_ISREG(entryInfo.st_mode))
            {
                names[*counter] = malloc(260*sizeof(char));
                ways[*counter] = malloc(260*sizeof(char));
                (names[*counter])[0]='\0';
                (ways[*counter])[0]='\0';

                strcat(names[*counter], de->d_name);
                strcat(ways[*counter], lab);
                (*counter)++;
            }
        }
        de=readdir( dir );
    }

    (void)closedir(dir);
    return 0;
}

int main()
{   int counter=0;
    char** names = malloc(4000*sizeof(char*));
    char** ways = malloc(4000*sizeof(char*));
    char** result = malloc(4000*sizeof(char*));
    int recount = 0;
    if (gointolab( "./labyrinth", names, ways, &counter) == 0)
    {
        find_minotaur("file.txt", names, ways, counter, result, &recount);
        FILE * xfile = fopen("result.txt", "w");
        while(recount!=0)
        {
            fputs(result[recount-1], xfile);
            fputs("\n", xfile);

            printf("%s\n",result[recount-1]);
            recount--;
        }
        fclose (xfile);
        for(int i=0;i<counter;i++){
            free(names[i]);
            free(ways[i]);
        }
        for(int i=0;i<recount;i++){
            free(result[i]);
        }
        free(names);
        free(ways);
        free(result);
        return 0;
    }
}
