#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a, const void* b){
    const char** word_1 = (const char**) a;
    const char** word_2 = (const char**) b;
    return strcmp(*word_1, *word_2);
}

int main(){
    char text[1000];
    char str[30];
    fgets(text, sizeof(char)*1000, stdin);
    fgets(str, sizeof(char)*30, stdin);
    char* str_new = strtok(str, " .\n");
    
    
    char* word = strtok(text, " .");
    int count_word = 0;
    char** words;
    words = malloc(sizeof(char*) * count_word);
    while(word){
        count_word++;
        words = realloc(words, sizeof(char*) * count_word);
        words[count_word-1] = word;
        word = strtok(NULL, " .");
        
    }
    
    qsort(words, count_word, sizeof(char*), cmp);
   
    char** result = bsearch(&str_new, words, count_word, sizeof(char*), cmp);
    
    free(words);
    
    if(result)
        puts("exists");
    else
        puts("doesn't exist");
    
    return 0;
}
