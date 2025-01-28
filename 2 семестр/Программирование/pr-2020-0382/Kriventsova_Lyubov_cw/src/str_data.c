#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include "structs.h"
#include "str_data.h"
void str_data(struct Sentence sent){
    int day, month, year;
    day = sent.countwords;
    month = sent.maxword;
    year = 1900 + sent.lent - 1;
    if (day < 10){
        if(month < 10){ wprintf(L" 0%d-0%d-%d\n", day, month, year);}
        else{wprintf(L" 0%d-%d-%d\n", day, month, year);}
    }
    else if(month < 10){wprintf(L" %d-0%d-%d\n", day, month, year);}
    else{wprintf(L" %d-%d-%d\n", day, month, year);}
}

