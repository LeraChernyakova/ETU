#include <locale.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "structures.h"

int cmp_2(const void * a, const void * b){
    struct Sentence* aa = (struct Sentence*)a;
    struct Sentence* bb = (struct Sentence*)b;
    int len_aa = 0, len_bb = 0;
    for (int i = 0; i < aa->num_words; i ++)
        len_aa = len_aa + wcslen(aa->words[i]);
    len_aa = len_aa / aa->num_words;
    for (int i = 0; i < bb->num_words; i ++)
        len_bb = len_bb + wcslen(bb->words[i]);
    len_bb = len_bb / bb->num_words;
    
    if (len_aa > len_bb)
        return 1;
    if (len_aa == len_bb)
        return 0;
    if (len_aa < len_bb)
        return -1;    
}

void sort_len_word(struct Text * txt){
    qsort(txt->sentence, txt->sent_count, sizeof(struct Sentence), cmp_2);
}
