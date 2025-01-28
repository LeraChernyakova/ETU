#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

void list_dir(char *dirPath,char* word,FILE* file) {
    DIR *dir = opendir(dirPath);                            // "открываем" директорию
    if (dir){                                              // если это удалось успешно
        struct dirent *de = readdir(dir);                  // получаем очередной элемент открытой директории
        while (de) {          // если это удалось
            if(de->d_name[0] != '.'){
                if(dirPath[strlen(dirPath)-1] != '/'){
                    dirPath[strlen(dirPath)+1] = '\0';
                    dirPath[strlen(dirPath)] = '/';
                }
                char dirPath_add[300];
                strcpy(dirPath_add,dirPath);
                strcat(dirPath_add,de->d_name);
                if(word[0] == de->d_name[0] && de->d_name[1] == '.'){
                    fprintf(file,"%s%s\n",dirPath, de->d_name);
                } else{
                    list_dir(dirPath_add,word,file);
                }
            }
            de = readdir(dir);                              // снова получаем очередной элемент открытой директории
        }
    }
    closedir(dir); // не забываем "закрыть" директорию
}

int main(){
    char tmp[100] = "/home/danil/Documents/CProject/hello_world_test";
    FILE *file;
    file = fopen("/home/danil/Documents/CProject/result.txt","w");
    char* word = (char*)malloc(30*sizeof(char));
    fgets(word,30,stdin);
    int len = (int)strlen(word);
    for(int i = 0;i<len;i++){
        list_dir(tmp,word+i,file);
    }
    fclose(file);
    free(word);
    return 0;
}

