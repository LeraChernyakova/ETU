#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <stdlib.h>
#include "structs.h"
#include "q_sort.h"

int compare(const void * a, const void * b){
    struct Sentence *first = (struct Sentence*) a;
    struct Sentence *second = (struct Sentence*) b;
    return ((int)first->len_of_3 - (int)second->len_of_3);
}

void q_sort(struct Text text){
    qsort(text.sentences, text.len_text, sizeof(struct  Sentence), compare);
}