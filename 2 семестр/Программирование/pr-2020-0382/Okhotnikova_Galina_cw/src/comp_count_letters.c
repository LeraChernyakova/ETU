#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <time.h>
#include "structs.h"
#include "comp_count_letters.h"

int comp_count_letters(struct Sentence* sent1, struct Sentence* sent2) {
    return sent1->count_k <= sent2->count_k;
}
