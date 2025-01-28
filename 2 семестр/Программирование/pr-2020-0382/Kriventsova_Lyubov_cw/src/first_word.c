#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include "structs.h"
#include "first_word.h"
int first_word(const void * item1, const void * item2){
    int lenitem1 = 0, lenitem2 = 0,i;
    struct Sentence* phrase1 = (struct Sentence*)item1;
    struct Sentence* phrase2 = (struct Sentence*)item2;
    for (i = 0; phrase1->phrase[i]!=L' ' && phrase1->phrase[i]!=L','; i++) lenitem1++;
    for (i = 0; phrase2->phrase[i]!=L' ' && phrase1->phrase[i]!=L','; i++) lenitem2++;
    return (lenitem1 - lenitem2);
}
