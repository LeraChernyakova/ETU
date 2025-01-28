#include <locale.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "structures.h"

struct Text search(struct Text* txt,  wchar_t ** str){
    struct Text res;
    wchar_t* mask = *str;
    int res_buf = 10;
    res.sentence = malloc(res_buf * sizeof(struct Sentence));
    res.sent_count = 0;
    
    for (int i = 0; i < txt->sent_count; i ++){
        int mark = 1;
        for (int k = 0; k < txt->sentence[i].num_words; k ++){
            if (wcslen(txt->sentence[i].words[k]) >= wcslen(mask) - 1){
                int str_indx = 0, msk_indx = 0;
                while ((mask[msk_indx] != '*') && (mark)){
                    if (mask[msk_indx] == '?'){
                        msk_indx ++;
                        str_indx ++;
                        wprintf(L"-*-%d\n", mark);
                    }
                    else if (mask[msk_indx] == txt->sentence[i].words[k][str_indx]){
                        msk_indx ++;
                        str_indx ++;
                    }
                    else mark = 0;
                    
                }
                if (mark){
                    msk_indx = wcslen(mask) - 1;
                    str_indx = wcslen(txt->sentence[i].words[k]) - 1;
                }
                while ((mask[msk_indx] != '*') && (mark)){
                    if (mask[msk_indx] == '?'){
                        msk_indx --;
                        str_indx --;
                    }
                    else if (mask[msk_indx] == txt->sentence[i].words[k][str_indx]){
                        msk_indx --;
                        str_indx --;
                    }
                    else mark = 0;
                }
                
            }
            else mark = 0;
        }
        if (mark){
            res.sentence[res.sent_count] = txt->sentence[i];
            res.sent_count ++;
            if (res_buf == res.sent_count + 2){
                res_buf = res_buf + 10;
                res.sentence = realloc(res.sentence, res_buf * sizeof(struct Sentence));
            }
        }
    }
    return res;    
}
