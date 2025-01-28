#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int cmp(const void* s1, const void* s2){
    char* ss1= *(char**)s1;
    char* ss2= *(char**)s2;
    //printf("%s %s %d\n",ss1,ss2,strcmp(ss1,ss2));
    return strcmp(ss1,ss2);
}

int main(){
    int n=1002;
    char text[n];
    int m=32;
    char* key=malloc(m*sizeof(char));
    fgets(text,n,stdin);
    fgets(key,m,stdin);
    int len=0;
    char** words = malloc(500*sizeof(char*));
    char* w=strtok(text," .");
    while(w){
        words[len++]=w;
        w=strtok(NULL," .");
    }
    qsort(words,len,sizeof(char*),cmp);
    /*for(int i=0;i<len;i++){
        printf("words %s\n",words[i]);
    }*/
    //printf("key %s %ld\n",key,strlen(key));
    if(strlen(key)<m-1){
        key[strlen(key)-1]='\0';}
    char**res;
    res = (char**) bsearch(&key,words,len,sizeof(char*),cmp);
    //printf("%s\n",*res);
    if(res){
        printf("exists");}
    else{
    printf("doesn't exists");}

    free(words);
    return 0;
}
