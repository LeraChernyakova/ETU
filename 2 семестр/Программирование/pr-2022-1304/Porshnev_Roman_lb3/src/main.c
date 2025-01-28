#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
void list_dir(const char *dirPath, char c, FILE* result){

    char *name;
    DIR *dir = opendir(dirPath);
    if(dir){
        struct  dirent *de = readdir(dir);
        while (de){
            if (strcmp(de->d_name, ".") && strcmp(de->d_name, "..")){
                char s[255];
                s[0] = '\0';
                strcat(s, dirPath);
                strcat(s, de->d_name);
                if (opendir(s) == NULL){
                    name = de->d_name;
                    if ((name[0] == c) && (name[1] == '.') && (name[2] == 't') && (name[3] == 'x') && (name[4] == 't') && (strlen(name) == 5)){
                        fprintf(result, "%s\n", s);
                        return;
                    }
                }else{
                    strcat(s, "/");
                    list_dir(s, c, result);
                }
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
}
char* readstring(){
    char c;
    char* string = NULL;
    string = malloc(sizeof(char));
    int symbols = 0;
    do{
        scanf("%c", &c);
        string = realloc(string, (symbols+1) * sizeof(char));
        string[symbols] = c;
        symbols += 1;
    }while (c != '\n');
    string[symbols-1] = '\0';
    return string;
}
int main(){
    FILE* result;
    result = fopen("result.txt", "w");
    int i;
    char *string = NULL;
    char* head_path = "./tmp/";
    string = readstring();
    for(i = 0; i<strlen(string); i++){
        list_dir(head_path, string[i], result);
    }
    free(string);
    fclose(result);
}
