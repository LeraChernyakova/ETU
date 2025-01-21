#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <string.h>
#include "structures.h"
#include "sortSentences.h"


void findUpper(struct Sentence* sen){
    int count = 0;
    wchar_t* str = sen -> string;
    for(int i = 0; i < sen -> len - 1; i++){
        if(iswupper(str[i])){
            count++;
        }
    }
    sen -> count_upper_symbol = count;
}

int compareSentences(const void* arg1, const void* arg2){
    struct Sentence** sen1 = (struct Sentence**) arg1;
    struct Sentence** sen2 = (struct Sentence**) arg2;
    return ((*sen1) -> count_upper_symbol - (*sen2) -> count_upper_symbol);
}

void sortSentences(struct Text text){
    for (int i = 0; i < text.len - 1; i++){
        findUpper(text.sentences[i]);
    } 
    qsort(text.sentences, text.len - 1, sizeof(struct Sentence*), compareSentences);
}