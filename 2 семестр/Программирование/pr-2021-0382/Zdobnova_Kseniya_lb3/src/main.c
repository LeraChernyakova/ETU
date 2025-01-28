#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int find_minotaur(char* name, char** names, char** paths, int cnt, char** ans, int* recount)
{
    int i;
    for(i = 0; i < cnt; i++)
    {
        if (strcmp(names[i], name) == 0)
            break;
    }
    char* way = malloc(260 * sizeof(char));
    way[0]='\0';
    strcat(way, paths[i]);
    strcat(way, "/");
    strcat(way, names[i]);

    FILE * open_file = fopen(way, "r");
    char* str = malloc(260 * sizeof(char));
    str[0]='\0';
    char* obj = malloc(260 * sizeof(char));
    obj[0]='\0';
    while(fscanf(open_file, "%s", str) != EOF) {
        if(strcmp(str, "@include")==0) {
            fscanf(open_file, "%s\n", obj);
            if (find_minotaur(obj, names, paths, cnt, ans, recount)) {
                ans[*recount] = malloc(256*sizeof(char));
                (ans[*recount])[0] = '\0';
                strcat(ans[*recount], way);
                (*recount)++;
                fclose (open_file);
                return 1;
            }
        }
        else if(strcmp(str, "Deadlock")==0) {
            fclose (open_file);
            return 0;
        }
        else if(strcmp(str, "Minotaur")==0) {
            ans[*recount] = malloc(260*sizeof(char));
            (ans[*recount])[0] = '\0';
            strcat(ans[*recount], way);
            (*recount)++;
            fclose (open_file);
            return 1;
        }
    }
    fclose (open_file);
    return 0;
}

int gointolab( char *lab, char** names, char** ways, int* counter)
{
    DIR *dir = NULL;
    struct dirent *de = NULL;
    char pathname[PATH_MAX + 1];
    dir = opendir(lab);
    if(dir == NULL)
        return -1;
    de = readdir(dir);
    while(de != NULL){
        struct stat entryInfo;
        if((strncmp( de->d_name, ".", PATH_MAX) == 0) || (strncmp( de->d_name, "..", PATH_MAX) == 0)){
            de = readdir(dir);
            continue;
        }
        (void)strncpy(pathname, lab, PATH_MAX);
        (void)strncat(pathname, "/", PATH_MAX);
        (void)strncat(pathname, de->d_name, PATH_MAX);
        if(lstat(pathname, &entryInfo)== 0){
            if(S_ISDIR(entryInfo.st_mode))
                gointolab(pathname, names, ways, counter);
            else if(S_ISREG(entryInfo.st_mode)) {
                names[*counter] = malloc(260*sizeof(char));
                ways[*counter] = malloc(260*sizeof(char));
                (names[*counter])[0]='\0';
                (ways[*counter])[0]='\0';

                strcat(names[*counter], de->d_name);
                strcat(ways[*counter], lab);
                (*counter)++;
            }
        }
        de = readdir(dir);
    }
    (void)closedir(dir);
    return 0;
}

int main()
{   int  cnt = 0;
    char** names = malloc(4000 * sizeof(char*));
    char** paths = malloc(4000 * sizeof(char*));
    char** ans = malloc(4000 * sizeof(char*));
    int recount = 0;
    if (gointolab( "./labyrinth", names, paths, &cnt) == 0)
    {
        find_minotaur("file.txt", names, paths, cnt, ans, &recount);
        FILE * open_file = fopen("result.txt", "w");
        while(recount!=0)
        {
            fputs(ans[recount-1], open_file);
            fputs("\n", open_file);

            printf("%s\n",ans[recount - 1]);
            recount--;
        }
        fclose (open_file);
        for(int i = 0; i < cnt; i++){
            free(names[i]);
            free(paths[i]);
        }
        for(int i = 0; i < recount; i++)
            free(ans[i]);
        free(names);
        free(paths);
        free(ans);
        return 0;
    }
}