#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <time.h>
#include "structs.h"
#include "count_letters.h"

int count_letters(struct Sentence *sent) {
    int cod;
    int k = 0;
    for (int i = 0; i < sent->len_s; i++) {
        cod = sent->s[i];
        if (cod >= 1040 && cod <= 1103) {
            k++;
        }
    }
    return k;
}
