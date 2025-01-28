#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <time.h>
#include "structs.h"
#include "delete_special_symb.h"

struct Text delete_special_symb(struct Text txt) {
    int fact1 = 1;
    for (int i = 0; i < txt.len_t; i++) {
        fact1 = 1;
        for (int j = 0; j < txt.newtxt[i].len_s; j++) {
            if (txt.newtxt[i].s[j] != '.' && txt.newtxt[i].s[j] != ',' && txt.newtxt[i].s[j] != ' '
            && !(iswalpha(txt.newtxt[i].s[j])) && !(iswdigit(txt.newtxt[i].s[j]))) {
                fact1 = 0;
            }
        }
        if (fact1) {
            for (int k = i; k < txt.len_t-1; k++) {
                txt.newtxt[k].s = txt.newtxt[k+1].s;
                txt.newtxt[k].len_s = txt.newtxt[k+1].len_s;
            }
            txt.len_t = txt.len_t - 1;
        }
    }
    return txt;
}
