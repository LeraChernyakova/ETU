#include <stdio.h>
#include <wchar.h>
#include "functions_for_sentence.h"

int check_kirl(struct Sentence* s){
    // проверяет, состоит ли предложение только из кириллических букв
    int i, j;
    wchar_t current_symbol;

    for (i = 0; i < s->words_number; i++){
        j = 0;
        while ((current_symbol = s->words[i].symbols[j++]) != '\0'){
            if ((current_symbol >= L'а' && current_symbol <= L'я') || (current_symbol >= L'А' && current_symbol <= L'Я')){
               continue; 
            } else {
                return 0;
            }
        }    
    }
    return 1;
}

void reverse(struct Sentence* s){
    struct Word word;
    int i;
    int last_index = (s->words_number / 2 - 1);
    for (i = 0; i <= last_index; i++){
        word = s->words[i];
        s->words[i] = s->words[s->words_number - i - 1];
        s->words[s->words_number - i - 1] = word;
    }
}

