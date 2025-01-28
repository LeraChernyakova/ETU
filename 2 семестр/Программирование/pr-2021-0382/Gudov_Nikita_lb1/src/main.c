#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int qsf(const void *a, const void *b)
{
    char** x=(char**)a;
    char** y=(char**)b;
    return strcmp(*x, *y);
}

int main(){
    char *text=(char*)malloc(1001);
    char *word=(char*)malloc(31);

    fgets( text,1001,stdin);
    text[strcspn(text, "\n")] = 0;
//**
    fgets(word,31,stdin);
    word[strcspn(word, "\n")] = 0;

    char **words=(char**)malloc(300*sizeof(char*));
    int i=0;
    char* cutword=strtok(text,". ");

    while (cutword != NULL) {
        words[i++] = cutword;
        cutword = strtok(NULL, ". ");
    }

    qsort(words, i, sizeof(char**), qsf);

    char ** t = bsearch(&word, words ,i, sizeof(char**), qsf);

    free(text);
    free(word);
    free(words);

    if(t)
    {printf("exists");}
    else
    {printf("doesn't exist");}
    return 0;
}