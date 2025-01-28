#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <stdlib.h>
#include "structs.h"
#include "replace.h"

void replace(struct Text text){
    for (int i = 0; i < text.len_text - 1; i++) { //в тексте
        if (text.sentences[i].num_of_words == 1)
            continue;
        else
            text.sentences[i + 1].words[0] = text.sentences[i].words[1];
    }
    if (text.sentences[text.len_text - 1].num_of_words > 1){
        text.sentences[0].words[0] = text.sentences[text.len_text - 1].words[1];

    }
}