#include <locale.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "structures.h"

int cmp(const void* a, const void* b){
    wchar_t** aa = (wchar_t**)a;
    wchar_t** bb = (wchar_t**)b;
    if (wcslen(*aa) > wcslen(*bb))
        return 1;
    if (wcslen(*aa) == wcslen(*bb))
        return 0;
    if (wcslen(*aa) < wcslen(*bb))
        return -1;
}


void less_order(struct Sentence* sent){

    qsort(sent->words, sent->num_words, sizeof(wchar_t*), cmp);
    int j = 0;
    for (int i = 0; i < sent->num_words;i ++){
        for (int k = 0; k < wcslen(sent->words[i]); k ++){
            sent->cur_sentence[j] = sent->words[i][k];
            j ++;
        }
        sent->cur_sentence[j] = sent->dots[i];
        j ++;      
    }
} 
