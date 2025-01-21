#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** read_text(){

    char c;
    char **text;
    int sentences = 0, symbols;
    text = NULL;
    do {
        text = realloc(text, (sentences + 1) * sizeof(char*));
        text[sentences] = NULL;
        symbols = 0;
        scanf(" ");
        do{
            scanf("%c", &c);
            text[sentences] = realloc(text[sentences], (symbols + 1) * sizeof(char));
            text[sentences][symbols] = c;
            symbols += 1;
        } while ((c != '.') && (c != ';') && (c != '?') && (c != '!'));
        text[sentences] = realloc(text[sentences], (symbols + 1) * sizeof(char));
        text[sentences][symbols] = '\0';
        sentences += 1;
    } while (strcmp(text[sentences - 1], "Dragon flew away!") != 0);
    return text;
}


char** filter(char **sentences, int sentences_count){

    int i = 0, check = 0, j;
    while (i < sentences_count){
        check = 0;
        for (j = 0; j < strlen(sentences[i]); j++)
            if ((sentences[i][j] > 64) && (sentences[i][j] < 91))
                check += 1;
        if (check > 1){
            free(sentences[i]);
            for(j = i; j < sentences_count - 1; j++)
                sentences[j] = sentences[j + 1];
            sentences_count--;
        }
        else
            i++;
    }
    return sentences;
}


int count(char **sentences){

    int i = 0;
    while (strcmp(sentences[i], "Dragon flew away!") != 0){
        i = i + 1;
    }
    return i;
}


void printtext(char **sentences, int n){

    int i;
    for(i = 0; i < n; i++)
        printf("%s\n", sentences[i]);
}


void free_text(char** sentences,  int n){

    int i;
    for(i = 0; i < n; i++)
        free(sentences[i]);
    free(sentences);
}


int main(){

    int i;
    char **sentences = read_text();
    int sentences_count = count(sentences);
    sentences = filter(sentences, sentences_count + 1);
    int new_sentences_count = count(sentences);
    printtext(sentences, new_sentences_count + 1);
    printf("Количество предложений до %d и количество предложений после %d\n", sentences_count, new_sentences_count);
    free_text(sentences, new_sentences_count + 1);
    return 0;
}
