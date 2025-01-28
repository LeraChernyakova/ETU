#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"
#include "task_3.h"

int compare(Word* el1,Word* el2){

    return el1->count_vovels >= el2->count_vovels;
}
void task_3(Text* text) {
    for (int i = 0; i < text->count_sent; i++) {
        qsort(text->text[i].words, text->text[i].count_words, sizeof(Word), (int (*)(const void *, const void *)) compare);
    }
}

