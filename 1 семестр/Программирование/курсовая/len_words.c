#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "processing_entered_text.h"
#include "len_words.h"

void len_words(struct Text* text)
{
    int* words_len;
    int len_w_now = 0;
    int size = 100;
    int size_last;
    wchar_t symb;
    words_len = (int*)calloc(size, sizeof(int));
    for (int i = 0; i < text -> cnt_sent; i++){
        for (int j = 0; j < (wcslen(text->sent[i]->str)); j++){
            symb = text -> sent[i] -> str[j];
            if (symb != L' ' && symb != L',' && symb != L'.' && symb != L'(' && symb != L')')
                len_w_now++;
            else{
                if (len_w_now >= size){
                    size_last = size;
                    size = len_w_now + 10;
                    words_len = (int*)realloc(words_len, sizeof(int) * size);
                    for (int k = size_last; k < size; k++)
                        words_len[k] = 0;
                }
                words_len[len_w_now] += 1;
                len_w_now = 0;
            }
        }
    }
    for (int i = 1; i < size; i++){
        if (words_len[i] != 0)
            wprintf(L"Количество слов длины %d = %d\n", i, words_len[i]);
    }
    free(words_len);
}
