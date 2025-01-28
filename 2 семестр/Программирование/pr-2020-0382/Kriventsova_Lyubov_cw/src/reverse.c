#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include "structs.h"
#include "reverse.h"
struct Sentence reverse(struct Sentence sent) {
    wchar_t *pt;
    int i, k, count = 0;
    wchar_t *new = malloc(sent.lent*sizeof(wchar_t *));
    if (sent.lent > 1) {
        sent.phrase[sent.lent - 1] = L'\0';
        sent.phrase = wcstok(sent.phrase, L" ,", &pt);
        while (sent.phrase != NULL) {
            sent.words[sent.countwords++] = sent.phrase;
            sent.phrase = wcstok(NULL, L" ,", &pt);
        }
        for (k = sent.countwords-1; k >= 0; k--){
        int quit = wcslen(sent.words[k]);
           if (count>0) { new[count]=L' ';
            count++;}
        for ( i = 0; i < quit; i++){
            new[count]= sent.words[k][i];
        count++;}
        }
        new[count++]=L'.';
        new[count]=L'\0';
        sent.phrase = new;
        sent.lent =wcslen(sent.phrase);
    }
    return sent;
}

