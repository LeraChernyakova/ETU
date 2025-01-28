#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convert(const void *a, const void *b){
    char** x = (char**)a;
    char** y = (char**)b;
    return strcmp(*x, *y);
}

int main(){
    char *text = (char*)malloc(1001);
    char *word = (char*)malloc(31);

    fgets( text,1001,stdin);
    text[strcspn(text, "\n")] = 0;
    fgets(word,31,stdin);
    word[strcspn(word, "\n")] = 0;

    char **words = (char**)malloc(300*sizeof(char*));
    int i=0;
    char* cwrd = strtok(text,". ");

    while (cwrd != NULL) {
        words[i++] = cwrd;
        cwrd = strtok(NULL, ". ");
    }
    qsort(words, i, sizeof(char**), convert);

    char ** res = bsearch(&word, words ,i, sizeof(char**), convert);

    if(res)
        printf("exists\n");
    else
        printf("doesn't exist\n");
    
    free(text);
    free(word);
    free(words);
    return 0;
}