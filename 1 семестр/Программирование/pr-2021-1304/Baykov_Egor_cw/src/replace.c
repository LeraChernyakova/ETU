#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include "replace.h"
#include "structures.h"

#define MEM_STEP 20;


//comment
wchar_t* readWord(){
    wprintf(L"Введите слова\n");
    int size = MEM_STEP;
    wchar_t* t = calloc(size, sizeof (wchar_t));
    wchar_t* word;
    wchar_t c;
    int i = 0;
    if(t != NULL){
        word = t;
    }
    do{
        if(i >= size - 2){
            size += MEM_STEP;
            t = realloc(word, sizeof(wchar_t) * size);
            if (t != NULL){
                word = t;
            }
            else{
                wprintf(L"Oops\n");
                return NULL;
            }
        }
        c = getwchar();
        word[i++] = c;
    } while (c != L'\n');
    word[i-1] = '\0';
    t = realloc(word, sizeof (wchar_t) * i);
    if (t != NULL){
        word = t;
    }
    else{
        wprintf(L"Oops\n");
        return NULL;
    }
    return word;
}

void replace(struct Text text){
    wchar_t* word_1 = readWord();
    wchar_t* word_2 = readWord();
    int diff = wcslen(word_2) - wcslen(word_1);
    for(int i = 0; i < text.len - 1; i++) {
        wchar_t *sent_copy = calloc(text.sentences[i]->len, sizeof(wchar_t));
        wcscpy(sent_copy, text.sentences[i]->string);
        wchar_t *pt;
        wchar_t *word = wcstok(sent_copy, L",. ", &pt);
        wchar_t *sent_out;
        size_t index;
        while (word != NULL) {
            if (wcscmp(word, word_1) == 0) {
                index = word - sent_copy;
                if (diff > 0) {
                    sent_out = calloc(wcslen(text.sentences[i]->string) + diff + 1, sizeof(wchar_t));
                } else {
                    sent_out = calloc(wcslen(text.sentences[i]->string) + 1, sizeof(wchar_t));
                }
                wcscpy(sent_out, text.sentences[i]->string);
                wmemmove(sent_out + index + wcslen(word_2), sent_out + index + wcslen(word_1),
                         wcslen(sent_out) - index - wcslen(word_1) + 1);
                wcsncpy(sent_out + index, word_2, wcslen(word_2));
                free(text.sentences[i]->string);
                text.sentences[i]->string = sent_out;
                text.sentences[i]->len = (int) wcslen(sent_out) + 1;
                sent_copy = realloc(sent_copy, text.sentences[i]->len * sizeof(wchar_t));
                wcscpy(sent_copy, text.sentences[i]->string);
                word = wcstok(sent_copy, L",. ", &pt);
            }
            word = wcstok(NULL, L",. ", &pt);
        }
    }
    free(word_1);
    free(word_2);
}
