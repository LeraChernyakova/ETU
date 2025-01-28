#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *p1, const void *p2)
{
    return strcmp(*(char**)p1,*(char**)p2);
}

int main(){
    int i = 0;
    char sym;
    char *phrase = malloc(1001*sizeof(char));
    char *str = malloc(31*sizeof(char));
    char **words = malloc(1000*sizeof(char*));
    char *ps;
    fgets( phrase,1001,stdin);
    fgets( str,31,stdin);
    phrase[strlen(phrase)]='\0';
    str[strlen(str)]='\0';
    ps = strtok(phrase, " .");
    while (ps != NULL) {
        words[i++] = ps;
        ps = strtok(NULL, " .");
    }
    qsort( words, i, sizeof(char**), cmp);
    char ** pointer;
    pointer = bsearch(&str, words,i, sizeof(char**), cmp);
    if(pointer)
    {
        printf("exists");
    }
    else
    {
        printf("doesn't exist");
    }
    free(phrase);
    free(words);
    free(str);
    return 0;
}
