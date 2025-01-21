#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include "addLetters.h"

int isvowel(wchar_t vowel){
    wchar_t vowels[] = L"AEIOUYaeiouyАЕЁИОУЫЭЮЯаеёиоуыэюя";
    if(wcschr(vowels, vowel) != NULL){
        return 1;
    }
    return 0;
}

void addLetters(struct Text text){
    wchar_t letters[] = L"АБВЕЁЖЗИЙКОПРУФХЫЬЭЮЯАБабвеёжзийкопруфхыьэюяфбABCEFGIJKOPQUVWYZAabcefgijkopquvwyza";
    int count_vowels;
    wchar_t* sen;
    wchar_t* some_sen;
    wchar_t* p;
    for (int i = 0; i < text.len - 1; i++){
        count_vowels = 0;
        sen = text.sentences[i] -> string;
        for(int j = 0; j < text.sentences[i] -> len - 1; j++){
            if(isvowel(sen[j])){
                count_vowels++;
            }
        }
        if(count_vowels){
            some_sen = malloc(sizeof(wchar_t) * (text.sentences[i] -> len + count_vowels));
            int j = 0, k = 0;
            while(sen[j] != L'\0'){
                if(isvowel(sen[j])){
                    p = wcschr(letters, sen[j]);
                    some_sen[k++] = *(p+1);
                    some_sen[k++] = *(p+2);
                    j++;
                }
                else{
                    some_sen[k++] = sen[j++];
                }
            }
            some_sen[k] = L'\0';
            free(sen);
            text.sentences[i] -> string = some_sen;
            text.sentences[i] -> len = k + 1;
        }
    }
}