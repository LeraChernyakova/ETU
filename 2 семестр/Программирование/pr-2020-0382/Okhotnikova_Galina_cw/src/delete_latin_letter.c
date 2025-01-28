#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <time.h>
#include "structs.h"
#include "delete_latin_letter.h"

struct Text delete_latin_letter(struct Text txt) {
    int cod;
    for (int i = 0; i < txt.len_t; i++) {
        for (int j = 0; j < txt.newtxt[i].len_s; j++) {
            cod = txt.newtxt[i].s[j];
            if (cod >= 65 && cod <= 90) {
                for (int k = j; k < txt.newtxt[i].len_s - 1; k++) {
                    txt.newtxt[i].s[k] = txt.newtxt[i].s[k+1];
                }
                txt.newtxt[i].len_s -= 1;
                j -= 1;
                txt.newtxt[i].s[txt.newtxt[i].len_s] = L'\0';
            }
        }
    }
    return txt;
}
