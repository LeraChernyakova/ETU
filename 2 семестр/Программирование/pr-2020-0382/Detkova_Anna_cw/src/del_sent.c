#include <locale.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "structures.h"

void delete_sentences(struct Text* txt){
    int i = 0;
    while (i < txt->sent_count){
        if ((txt->sentence[i].num_words < 2) || (txt->sentence[i].num_words > 5)){
            for (int k = i; k < txt->sent_count - 1; k ++){
                txt->sentence[i] = txt->sentence[i + 1];
            }
            txt->sent_count --;
            i --;
        }
        i ++;
    }
}
