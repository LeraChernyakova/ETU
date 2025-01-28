#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"
#include "task_2.h"

void task_2(Text* text){
    int words_up_let;
    int i = 0;
    while (i < text->count_sent){
        words_up_let = 0;
        for (int j = 0; j < text->text[i].count_words; j++){
            if (text->text[i].words[j].up_let){
                words_up_let++;
            }
        }

        if(words_up_let != text->text[i].count_words){
            if(i == text->count_sent-1){
                text->count_sent--;
                break;
            }
            for(int j = 0; j < text->text[i].count_mask;j++){
                free(text->text[i].masks[j]);
            }
            free(text->text[i].masks);
            free(text->text[i].sent);
            free(text->text[i].words);
            if(i != text->count_sent-1){
            	for (int k = i;k < text->count_sent-1;k++){
                text->text[k+1].index_sent = text->text[k].index_sent;
                text->text[k] = text->text[k+1];
            	}
            }
            text->count_sent--;
            i--;
        }
        i++;
    }
}

