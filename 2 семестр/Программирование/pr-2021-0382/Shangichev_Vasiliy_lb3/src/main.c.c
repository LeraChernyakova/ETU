#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void write(char** answer, int len){
    int i;
    FILE* fp;
    fp = fopen("result.txt", "w");
    for (i = 0; i < len; i++){
        fprintf(fp, "%s\n", answer[i]);
    }
    fclose(fp);
}

int check(char* name, const char* word){
    /*
    проверяет, является ли название файла
    ответом. если да, то возвращает нужный
    индекс.
    */
    if (name[1] != '.'){
        return -1;
    }
    int i, len = strlen(word);
    for (i = 0; i < len; i++){
        if (name[0] == word[i]){
            return i;
        }
    }
    return -1;
}

void listDir(const char* path, const char* word, char** answer){
    // готовим следующий путь
    char next[150];
    strcpy(next, path);
    strcat(next, "/");
    
    // открываем текущую директорию и 
    // перебираем файлы и папки
    DIR* dir = opendir(path);
    struct dirent* de = readdir(dir);
    while (de){
        if (de->d_type == DT_REG){
            // если это файл, то проверяем, не
            // является ли он частью ответа
            int answer_i = check(de->d_name, word);
            if (answer_i != -1){
                strcpy(answer[answer_i], next);
                strcat(answer[answer_i], de->d_name);
            }
        }
        if (de->d_type == DT_DIR && strcmp(de->d_name, ".") \
            && strcmp(de->d_name, "..")){
            int len = strlen(next);
            strcat(next, de->d_name);
            listDir(next, word, answer);
            next[len] = '\0';
        }
        de = readdir(dir);
    }
    closedir(dir);
}

int main(){
    char word[50];
    scanf("%s", word);
    int i, len = strlen(word);
    char** answer = malloc(sizeof(char*) * len);
    for (i = 0; i < len; i++){
        answer[i] = malloc(sizeof(char) * 100);
        answer[i][0] = '\0';
    }
    listDir("./tmp", word, answer);
    write(answer, len);
    for (i = 0; i < len; i++){
        free(answer[i]);
    }
    free(answer);
    return 0;
}



