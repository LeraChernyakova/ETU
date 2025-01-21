#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "processing_entered_text.h"
#include "shift_words.h"

void shift_words(struct Text* text){
    int N;
    wprintf (L"Введите целое положительное число N,на которое хотите сделать сдвиг предложений:\n");
    wscanf (L"%d", &N);
    if(N > 0){
        int len_word;
        int index_last;
        int ind_symb = 0;
        int word_size = 10;
        wchar_t symb;
        wchar_t wchar;
        wchar_t* word;
        word = (wchar_t*)malloc(sizeof(wchar_t) * word_size);
        for (int l = 0; l < N; l++){
            for (int i = 0; i < text -> cnt_sent; i++){
                ind_symb = 0;
                len_word = 0;
                index_last = text -> sent[i] -> len - 1;
                int j = index_last;
                while (text -> sent[i] -> str[j] != L' ' && text -> sent[i] -> str[j] != L',' && j != 0){
                    len_word++;
                    j--;
                    if (j == 0)
                        len_word++;
                }
                if (text -> sent[i] -> str[j] == L' ')
                    symb = L' ';
                else if (text -> sent[i] -> str[j] == L',')
                    symb = L',';
                for (int m = j + 1; m < wcslen(text -> sent[i] -> str) - 1; m++){
                    if (ind_symb == word_size - 2)
                    {
                        word_size *= 2;
                        word = (wchar_t*)realloc(word, sizeof(wchar_t) * word_size);
                    }
                    word[ind_symb] = text -> sent[i] -> str[m];
                    ind_symb++;
                }
                for (int m = text -> sent[i] -> len - 1; m != (len_word); m--){
                    wchar = text -> sent[i] -> str[m - (len_word + 1)];
                    if (wchar == L' ' || wchar == L','){
                        text -> sent[i] -> str[m] = symb;
                        symb = wchar;
                    }
                    else
                        text -> sent[i] -> str[m] = text -> sent[i] -> str[m - (len_word + 1)];
                }
                for (int m = 0; m < len_word; m++){
                    text -> sent[i] -> str[m] = word[m];
                    if (m == len_word - 1) 
                        text -> sent[i] -> str[m + 1] = symb;
                }
                for (int m = 0; m < word_size; m++)
                    word[m] = '\0';
                text -> sent[i] -> str[index_last + 2] = '\0';
            }
        }
        free(word);
    }
    else
        wprintf(L"Введено неккоректное значение для свдига предложений!Выберете другую функцию или обратитесь к этой же,но с корректным значением!\n");
}
