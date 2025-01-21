#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include "structures.h"
#include "findAnagram.h"

int compareLetters(const void* arg1, const void* arg2){
    wchar_t* sign1 = (wchar_t*) arg1;
    wchar_t* sign2 = (wchar_t*) arg2;
    return *sign1 - *sign2;
}

void kickSymbols(struct Sentence* sen){
    int count = 0;
    wchar_t* str = sen -> string;
    for(int i = 0; i < sen -> len; i++){
        if(str[i] != L' ' && str[i] != L'.' && str[i] != L','){
            count++;
        }
    }
    sen -> count = count;
}

wchar_t* copyAndSort(struct Sentence* sen){
    kickSymbols(sen);
    wchar_t* str = malloc(sizeof(wchar_t) * (sen -> count));
    wchar_t c;
    int j = 0;
    for(int i = 0; i < sen -> len; i++){
        c = sen -> string[i];
        if(c != L'.' && c != L'\'' && c != L',' && c != L' '){
            str[j++] = c;
        }
    }
    qsort(str, sen -> count - 1, sizeof(wchar_t), compareLetters);
    return str;
}

void findAnagram(struct Text text){
    wchar_t* sen_1;
    wchar_t* sen_2;
    for(int i = 0; i < text.len - 2; i++){
        sen_1 = copyAndSort(text.sentences[i]);
        for(int j = i + 1; j < text.len - 1; j++){
            sen_2 = copyAndSort(text.sentences[j]);
            if(wcslen(sen_1) == wcslen(sen_2)){
                if(!(wcsncmp(sen_1, sen_2, wcslen(sen_1)))){
                    wprintf(L"%ls -- %ls -- Anagrams\n", text.sentences[i] -> string, text.sentences[j] -> string);
                }
            }
            free(sen_2);
        }
        free(sen_1);
    }
}