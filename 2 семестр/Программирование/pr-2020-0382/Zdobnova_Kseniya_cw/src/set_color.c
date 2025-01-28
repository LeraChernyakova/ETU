#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <stdlib.h>
#include "structs.h"
#include "set_color.h"

#define NONE "\033[0m"
#define GREEN "\033[42m"


void set_color(struct Text text){
    int flag = 0;
    for (int i = 0; i < text.len_text; i++) { //в тексте
        for (int j = 0; j < text.sentences[i].num_of_words; j++) { //в предложении
            if (wcslen(text.sentences[i].words[j]) != 1)
                for (int k = 1; k < wcslen(text.sentences[i].words[j]) - 1; k++){
                    if (iswdigit(text.sentences[i].words[j][k])){
                        wprintf(L"%s%ls", GREEN, text.sentences[i].words[j]);
                        wprintf(L"%s%c", NONE, text.sentences[i].separator[j]);
                        flag = 1;
                        break;
                    }
                }
            else{
                if (iswdigit(text.sentences[i].words[j][0])) {
                    wprintf(L"%s%ls", GREEN, text.sentences[i].words[j]);
                    wprintf(L"%s%c", NONE, text.sentences[i].separator[j]);
                    flag = 1;
                }
            }
            if (flag == 0)
                wprintf(L"%ls%c", text.sentences[i].words[j], text.sentences[i].separator[j]);
            flag = 0;
        }
    }
    wprintf(L"\n");
}