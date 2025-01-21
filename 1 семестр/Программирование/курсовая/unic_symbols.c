#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "processing_entered_text.h"
#include "unic_symbols.h"

void unic_symbols(struct Text* text){
    wchar_t *sent_now;
    wchar_t *sent_comp;
    int unic_symb;
    int cnt_unic = 0;
    wprintf (L"Уникальные символы:\n");
    for(int i = 0; i < text->cnt_sent; i++){
        sent_now = text -> sent[i] -> str;
        for (int j = 0; j < wcslen(sent_now); j++){
            if (iswalpha(sent_now[j]) != 0){
                unic_symb = 0;
                for (int k = 0; k < text -> cnt_sent; k++){
                    sent_comp = text -> sent[k] -> str;
                    for (int l = 0; l < wcslen(sent_comp); l++){
                        if (iswalpha(sent_comp[l]) != 0){
                            if ((sent_now[j] == sent_comp[l]) && (j != l)){
                                unic_symb = 1;
                                break;
                            }
                        }
                    }
                }
                if (unic_symb == 0){
                    wprintf (L"%lc ", sent_now[j]);
                    cnt_unic += 1;
                }
            }
        }
    }
    if (cnt_unic == 0)
        wprintf (L"Уникальные символы отсутсвуют.\n");
    wprintf (L"\n");
}
