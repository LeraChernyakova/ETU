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
#include "count_letters.h"
#include "comp_count_letters.h"
#include "delete_special_symb.h"
#include "delete_latin_letter.h"


int main() {
    int operation;
    int identic = 0;
    int memory = 100, i;
    wchar_t symb;
    setlocale(LC_ALL, "");
    struct Text txt;
    txt.len_t = 0;
    txt.newtxt = malloc(memory*sizeof(struct Sentense *));
    int fact = 1;

    wprintf(L"Здравствуйте!\n"
            "Введите, пожалуйста, текст, который хотите обработать, "
            "закончив свой ввод символом перевода строки.\n");

    while (fact) {
        struct Sentence sent;
        sent.s = malloc(memory*sizeof(wchar_t));
        memory = memory*2;
        sent.len_s = 0;
        symb = (wchar_t) fgetwc(stdin);

        if (symb == L'\n') {
            fact = 0;
        }

        else {
            while (symb == L' ') {
                symb = (wchar_t) fgetwc(stdin);
            }
            sent.s[sent.len_s++] = symb;
            while (symb != L'.') {
                symb = (wchar_t) fgetwc(stdin);
                sent.s[sent.len_s++] = symb;
            }

            if (sent.len_s == memory) {
                memory = memory*2;
                sent.s = realloc(sent.s, memory*sizeof(wchar_t));
            }
        }
        if (symb ==  L'.') {
            sent.s[sent.len_s+1] = L'\0';
        }
        for (i = 0; i < txt.len_t; i++) {
            identic = 1;
            for (int j = 0; j < sent.len_s && j < txt.newtxt[i].len_s; j++){
                if (towlower(sent.s[j]) != towlower(txt.newtxt[i].s[j])) {
                    identic = 0;
                }
            }
        }
        if (identic == 0) {
            txt.newtxt[txt.len_t++] = sent;
        }
        if (txt.len_t == memory) {
            memory = memory*2;
            txt.newtxt = realloc(txt.newtxt, memory*sizeof(struct Sentence *));
        }
    }

    wprintf(L"Введите, пожалуйста, одну из команд:\n"
            "0: Выход из программы\n"
            "1: Вывод номеров предложений, в которых встречается подстрока 'часы: минуты' и количества минут до текущего времени\n"
            "2: Удаление заглавных латинских букв во всех предложениях\n"
            "3: Сортировка предложений по уменьшению количеству кириллических букв\n"
            "4: Удаление предложений, в которых нет специальных символов\n"
            "5: Вывод отредактированного текста на экран\n");
    do {
        wscanf(L"%d", &operation);

        switch (operation) {

            case 0:
                for (int a = 0; a < txt.len_t; a++) {
                    free(txt.newtxt[a].s);
                }
                free(txt.newtxt);
                exit;
                break;
            case 1:
                find_time(&txt);
                for (int b = 0; b < txt.len_t; b++) {
                    if (txt.newtxt[b].time_s[0] != L'a') {
                        wprintf(L"Номер предложения: %d\n", b);
                        wprintf(L"Минут до текущего времени: %ld\n", txt.newtxt[b].diff_t);
                    }
                }

                break;
            case 2:
                txt = delete_latin_letter(txt);
                break;
            case 3:
                for (int a = 0; a < txt.len_t; a++) {
                    txt.newtxt[a].count_k = count_letters(&txt.newtxt[a]);
                }
                qsort(txt.newtxt, txt.len_t, sizeof(struct Sentence), (int (*)(const void *, const void *))comp_count_letters);
                break;
            case 4:
                txt = delete_special_symb(txt);
                break;
            case 5:
                for (int k = 0; k < txt.len_t; k++) {
                    wprintf(L"%ls", txt.newtxt[k].s);
                }
                wprintf(L"\n");
                break;
            default:
                wprintf(L"Данные некорректны");
        }
    } while(operation != 0);
    return 0;
}
