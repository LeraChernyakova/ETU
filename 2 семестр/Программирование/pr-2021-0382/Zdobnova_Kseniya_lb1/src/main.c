#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b){
    return strcmp(*(char**)a, *(char**)b);
 }

int main(){
    char *text = malloc(1001 * sizeof(char));
    char **words = malloc(1001 * sizeof(char*));;
    char *str = malloc(31 * sizeof(char));
    int words_in_text = 0;
    fgets(text, 1001, stdin);
    fgets(str, 31, stdin);
    text[strlen(text)] = '\0';
    str[strlen(str)] = '\0';
    char *word = strtok(text, " .");
    while(word != NULL){
        words[words_in_text] = word;
        words_in_text++;
        word = strtok(NULL, " .");
    }
    qsort(words, words_in_text, sizeof(char**), compare);
    char **arg = (char**) bsearch(&str, words, words_in_text, sizeof(char**), compare);
    if(arg != NULL)
        printf("exists");
    else
        printf("doesn't exist");
    free(words);
    free(text);
    free(str);
    return 0;
}
