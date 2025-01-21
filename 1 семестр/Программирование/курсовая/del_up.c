#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "processing_entered_text.h"
#include "del_up.h"

void del_up(struct Text* text){
    int len_word;
    int size;
    int len_no_up;
    int i = 0;
    wchar_t* copy_str;
    wchar_t* buffer;
    wchar_t* ptr;
    wchar_t* del_word;
    size = wcslen(text->sent[i]->str) + 2;
    copy_str = (wchar_t*)malloc(sizeof(wchar_t) * size);
    while (i < text -> cnt_sent){
        if (wcslen(text -> sent[i] -> str) > size){
            size = wcslen(text -> sent[i] -> str) + 2;
            copy_str = (wchar_t*)realloc(copy_str, sizeof(wchar_t) * size);
        }
        wcsncpy(copy_str, text -> sent[i] -> str, size);
        ptr = wcstok(copy_str, L", .", &buffer);
        while (ptr != NULL){
            len_word = wcslen(ptr);
            if (iswupper(ptr[len_word - 1])){
                del_word = wcsstr(text -> sent[i] -> str, ptr);
                len_no_up = wcslen(del_word) - len_word;
                if (del_word[len_word] == L'.'){
                    *(del_word) = '\0';
                    if (text-> sent[i] -> words != 1){
                        *(del_word - 1) = '.';
                    }
                }
                else{
                    wmemmove(del_word, del_word + len_word + 1, len_no_up);
                    *(del_word + len_no_up) = '\0';
                }
                text -> sent[i] -> len = wcslen(text -> sent[i] -> str);
                text -> sent[i] -> words -= 1;
            }
            ptr = wcstok(NULL, L", .", &buffer);
        }
        i++;
    }
    free(copy_str);
}
