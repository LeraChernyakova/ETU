#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "structures.h"
#include "other_funcs.h"

#define INIT_SIZE 50

int sort_sent(const void* arg1, const void* arg2){
    int i;
    int count_lat1 = 0;
    int count_lat2 = 0;
    struct Sentence* Sent1 = (struct Sentence*)arg1;
    struct Sentence* Sent2 = (struct Sentence*)arg2;
    for (i=0; i<Sent1->len_s; i++){
        if (isalpha(Sent1->sentence[i])) count_lat1++;
    }
    for (i=0; i<Sent2->len_s; i++){
        if (isalpha(Sent2->sentence[i])) count_lat2++;
    }
    return count_lat2 - count_lat1;
} 
