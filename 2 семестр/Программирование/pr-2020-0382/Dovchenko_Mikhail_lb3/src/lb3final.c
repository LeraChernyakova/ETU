#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50
#define ADD 50


char* readtext();
char* delete(char*);
char* edit(char*);

int main(){
    char* terminalstr = "Dragon flew away!";
    char** textarr = malloc(SIZE*sizeof(char*));
    int arraylength = 0, counteraft = 0, i;
    char* str;
    int size_textarr = SIZE;

    while(1){
        str = readtext();
        str = edit(str);
        if(!strcmp(textarr[arraylength++] = str, terminalstr)){
            break;
        }
        if(arraylength == size_textarr){
            size_textarr += ADD;
            textarr = realloc(textarr, size_textarr*sizeof(char*));
        }
    }
    for(i = 0; i <= arraylength;){
        if(!strcmp(textarr[i], terminalstr)){
            i++;
            break;}
        if(!strcmp(textarr[i], "\0")){
            for(counteraft = i; counteraft < arraylength; counteraft++){
                textarr[counteraft] = textarr[counteraft+1];}
        }
        else
            i++;

    }
    for (int j = 0; j < i; j++){
        puts(textarr[j]);
        free(textarr[j]);
    }
    printf("Количество предложений до %d и количество предложений после %d", arraylength-1, i-1);
    free(textarr);
    return 0;
}


char* readtext(){
    int length = 0, size = SIZE, c;
    char *text = malloc(size*sizeof(char));
    while(1){
        c = getchar();
        text[length++] = c;
        if(length == size){
            size += ADD;
            text = realloc(text, size);
        }
        if(c == '.' || c == ';' || c == '?' || c == '!')
            break;
    }
    text[length]='\0';
    return text;
}


char* edit(char* e_str){
    int e_len = strlen(e_str), e_counter1;
    while(e_str[0] == ' ' || e_str[0] == '\t' || e_str[0] == '\n'){
        for(e_counter1 = 0; e_counter1 < e_len; e_counter1++){
            e_str[e_counter1] = e_str[e_counter1 + 1];
        }
    }
    e_str = delete(e_str);
    return e_str;
}


char* delete(char* del_str){
    if(del_str[(strlen(del_str)-1)] == '?'){
        del_str = "\0";
    }
    return del_str;
}
