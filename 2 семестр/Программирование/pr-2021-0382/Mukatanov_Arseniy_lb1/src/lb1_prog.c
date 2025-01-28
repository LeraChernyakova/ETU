#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF 10

int compare(const void* str1, const void* str2);

int main(){
    char* text1 = malloc(1001*sizeof(char));
    char* str = malloc(31*sizeof(char));
    fgets(text1, 1001, stdin);
    fgets(str, 31, stdin);
    text1[strlen(text1)] = '\0';
    str[strlen(str)] = '\0';
    char* tok;
    tok = strtok(text1, " .");
    int buf = BUF;
    int i = 0;
    char** text2 = calloc(buf, sizeof(char*));
    while(tok != NULL){
        text2[i] = tok;
        i++;
        if(i == buf - 1){
            buf += BUF;
            text2 = realloc(text2,buf*sizeof(char*));
        }
        tok = strtok(NULL, " .");
    }
    qsort(text2, i, sizeof(char*), compare);
    char** item = bsearch(&str, text2, i, sizeof(char**), compare);

    if(item != NULL){
        printf("exists");
    }
    else{
        printf("doesn't exist");
    }
    free(text1);
    free(text2);
    free(str);
    return 0;
}

int compare(const void* str1, const void* str2){
    return strcmp(*(char**)str1, *(char**)str2);
}