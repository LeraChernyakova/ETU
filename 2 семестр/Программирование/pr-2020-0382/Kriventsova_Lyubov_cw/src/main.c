#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include "first_word.h"
#include "right_proposal.h"
#include "reverse.h"
#include "str_data.h"
#include "structs.h"

int main() {
    int flag = 1, yes = 1, same = 0;
    wchar_t sym, command;
    int addmemory = 100;
    struct Sentence ex;
    setlocale(LC_ALL, "");
    struct Text tex;
    wprintf(L"Вас приветствует программа по обработке текста!\n"
            "Пожалуйста, введите текст, который следует отредактировать:\n"
            "(Чтобы закончить ввод, следует нажать ""enter"", спасибо). \n");
    tex.text = malloc(addmemory * sizeof(struct Sentence));
    tex.len = 0;
    do {
        struct Sentence sent;
        sent.phrase = malloc(addmemory * sizeof(wchar_t));
        sent.words = malloc(addmemory * sizeof(wchar_t *));
        addmemory *= 2;
        sent.lent = 0;
        sent.maxword = 0;
        sent.countwords = 0;
        sent.right = 1;
        sym = (wchar_t) fgetwc(stdin);
        if (sym == L'\n') flag = 0;
        else {
            //while(sym = L' ') {sym = (wchar_t)fgetwc(stdin);}
            while (sym == L' ') sym = (wchar_t) fgetwc(stdin);
            sent.phrase[sent.lent++] = sym;
            do {
                sym = (wchar_t) fgetwc(stdin);
                sent.phrase[sent.lent++] = sym;
                if (sent.lent == addmemory) {
                    addmemory *= 2;
                    sent.phrase = realloc(sent.phrase, addmemory * sizeof(wchar_t));
                    sent.words = realloc(sent.words, addmemory * sizeof(wchar_t *));
                }
            } while (sym != L'.');
            sent.phrase[sent.lent] = L'\0';
            for (int k = 0; k < tex.len; k++) {
                ex = tex.text[k];
                same = 1;
                for (int j = 0; j < sent.lent && j < ex.lent; j++) {
                    if ((wchar_t) towlower(sent.phrase[j]) != (wchar_t) towlower(ex.phrase[j])) {
                        same = 0;
                        break;
                    }
                }
                if (same) {
                    yes = 0;
                    break;
                }
            }
            if (yes == 1) {
                tex.text[tex.len++] = sent;
                if (tex.len == addmemory) {
                    addmemory *= 2;
                    tex.text = realloc(tex.text, addmemory);
                }
            }
        }
        yes = 1;
    } while (flag == 1);
    while (command != L'0') {
        wprintf(L"\nЧтобы выбрать одну из возможных команд, "
                "введите в терминал соответствующую цифру:\n"
                "0 - Выйти из программы;\n"
                "1 - Вывести строку-дату для каждого предложения;\n"
                "2 - Отредактировать предложения так, чтобы слова шли в обратном порядке;\n"
                "3 - Отсортировать предложения по длине первого слова в предложении;\n"
                "4 - Удалить предложения, у которых все слова имеют длину не больше трёх символов;\n"
                "5 - Вывести преобразованный текст на экран.\n");
        wscanf(L"%ls", &command);
        switch (command) {
            case L'0':
            {for (int i = 0; i <= tex.len-1; i++){
                    free(tex.text[i].phrase);
                    free(tex.text[i].words);
                }
                free(tex.text);
            }
                break;
            case L'1': {for (int k = 0; k<=tex.len-1; k++){
                    wprintf(tex.text[k].phrase);
                    ex =  right_proposal(tex.text[k]);
                    str_data(ex);
                }
            }
                break;
            case L'2': {
                for (int k = 0; k<=tex.len-1; k++){
                    tex.text[k] = reverse(tex.text[k]);
                }
            }
                break;
            case L'3': {
                qsort( tex.text, tex.len, sizeof(struct Sentence), first_word);
            }
                break;
            case L'4': {
                for (int k = 0; k<=tex.len-1; k++){
                    ex =  right_proposal(tex.text[k]);
                    if (ex.right == 0) {
                        for (int r = k; r<tex.len-1; r++) {
                            tex.text[r].phrase = tex.text[r+1].phrase;
                            tex.text[r].lent = tex.text[r+1].lent;
                        }
                        free(tex.text[tex.len].phrase);
                        tex.len -=1;
                    }
                }
            }
                break;
            case L'5': {
                for (int i = 0; i <= tex.len-1; i++)
                    wprintf(L"%ls ", tex.text[i].phrase);
            }
                break;
            default:
                wprintf(L"Данные некорректны");
                break;
        }
    }
    return 0;
}
