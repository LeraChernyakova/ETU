#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SENT_NUM 10
int cmpr(const void* a,const void* b){
    return strcmp(*(char**)a,*(char**)b);
}
int main(){
    char* str=malloc(1001*sizeof(char));
    char* word=malloc(31*sizeof(char));
    fgets(str,1001,stdin);
    fgets(word,31,stdin);
    str[strlen(str)-1]='\0';
    word[strlen(word)-1]='\0';

    char* pch=strtok(str," .");
    int sent_num=SENT_NUM;
    int i=0;
    char** text=calloc(sent_num,sizeof(char*));
    while(pch!=NULL){
        text[i++]=pch;
        if(i==sent_num){
            sent_num*=2;
            text=realloc(text,sent_num*sizeof(char*));
        }
        pch=strtok(NULL," .");
    }

    qsort(text,i,sizeof(char**),cmpr);
    char** pItem;
    pItem=bsearch(&word,text,i,sizeof(char**),cmpr);
    if(pItem!=NULL)
        printf("exists");
    else
        printf("doesn't exist");
    free(text);
    free(str);
    free(word);
    return 0;
}
