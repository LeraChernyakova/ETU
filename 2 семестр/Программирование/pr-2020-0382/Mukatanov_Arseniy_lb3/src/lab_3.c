#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER 50
#define ADD_MORE 50

char* delete(char* b_str){
    int count = 0;
    for(int i = 0; i < strlen(b_str); i++){
        if(isupper(b_str[i])){
            count++;
        }
    }
    if(count > 1){
        b_str = "\0";
    }
    return b_str;
}

char* reading(){
    int len = 0, size = BUFFER, a;
    char *text = malloc(size*sizeof(char));
    while(1){
        a = getchar();
        text[len++] = a;
        if(len == size){
            size += ADD_MORE;
            text = realloc(text, size);
        }
        if(a == '.' || a == ';' || a == '?' || a == '!')
            break;
    }
    text[len]='\0';
    return text;
}

char* fixing(char* a_str){
    int a_len = strlen(a_str);
    while(a_str[0] == ' ' || a_str[0] == '\t' || a_str[0] == '\n'){
        for(int i = 0; i < a_len; i++){
            a_str[i] = a_str[i + 1];
        }
    }
    a_str = delete(a_str);
    return a_str;
}



int main(){
    char* default_str = "Dragon flew away!";
    char** arr = malloc(BUFFER*sizeof(char*));
    int arrlen = 0, counter = 0, i;
    char* str;
    int size_arr = BUFFER;
    while(1){
        str = reading();
        str = fixing(str);
        arr[arrlen] = str;
        if(!strcmp(arr[arrlen++], default_str)){
            break;
        }
        if(arrlen == size_arr){
            size_arr += ADD_MORE;
            arr = realloc(arr, size_arr*sizeof(char*));
        }
    }
    for(i = 0; i <= arrlen;){
        if(!strcmp(arr[i], default_str)){
            i++;
            break;}
        if(!strcmp(arr[i], "\0")){
            for(counter = i; counter < arrlen; counter++){
                arr[counter] = arr[counter+1];}
        }
        else
            i++;

    }
    for (int j = 0; j < i; j++){
        puts(arr[j]);
        free(arr[j]);
    }
    printf("Количество предложений до %d и количество предложений после %d", arrlen-1, i-1);
    free(arr);
    return 0;
}
