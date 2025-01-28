#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <time.h>
#include "structs.h"
#include "find_time.h"

void find_time(struct Text *txt) {
    time_t now = time(NULL);
    struct tm* now2 = localtime(&now);
    long int now_inm;
    now_inm = (now2->tm_hour)*60 + now2->tm_min;
    int k;
    long hours, minutes, time_inm;
    wchar_t* end;
    for (int i = 0; i < txt->len_t; i++) {
        k = 0;
        txt->newtxt[i].time_s = malloc(5*sizeof(wchar_t));
        txt->newtxt[i].time_s[0] = L'a';
        for (int i1 = 0; i1 < txt->newtxt[i].len_s-5; i1++) {
            if ((txt->newtxt[i].s[i1] == '0' || txt->newtxt[i].s[i1] == '1' || txt->newtxt[i].s[i1] == '2')
                 && iswdigit(txt->newtxt[i].s[i1 + 1]) && txt->newtxt[i].s[i1 + 2] == ':'
                 && iswdigit(txt->newtxt[i].s[i1 + 3]) && iswdigit(txt->newtxt[i].s[i1 + 4])) {
                for (int j = i1; j < i1 + 5; j++) {
                    txt->newtxt[i].time_s[k++] = txt->newtxt[i].s[j];
                }
                hours = wcstol(txt->newtxt[i].time_s, &end, 10);
                minutes = wcstol(end+1, NULL, 10);
                time_inm = hours*60 + minutes;
                if (now_inm >= time_inm) {
                    txt->newtxt[i].diff_t = now_inm - time_inm;
                }
                else {
                    txt->newtxt[i].diff_t = (time_inm - now_inm) + 720;
                }
            }
        }
    }
}
