#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "funcs_for_tasks.h"
#include "other_funcs.h"
#include "input_text.h"
#include "structures.h"

#define INIT_SIZE 50

int main(){
    setlocale(LC_ALL, "");
    wprintf(L"Введите текст: \n");
    int i,j;
    int res1, res4;
    struct Text text = read_text();

    wprintf(L"Выберите команду, которую необходимо выполнить:\n"
            "0. Выход.\n"
            "1. Для каждого предложения вывести 'Палиндромы на месте!' если все слова являются палиндромами,"
            "'Кто-то потерял все палиндромы.' если ни одного слово не является палиндромом, в остальных случаях 'Чего-то не хватает.';\n"
            "2. Заменить все специальные символы (включая .,;) в тексте на подстроку “>special symbol<”;\n"
            "3. Отсортировать предложения по уменьшению количества латинских букв;\n"
            "4. Удалить все предложения в которых в одном слове встречаются латинские и кириллические буквы;\n"
            "5. Вывести измененный текст.\n");
    int command;
    wscanf(L"%d", &command);
    while(command != 0) {
        switch (command) {
            case 1: {
                for (i = 0; i < text.len_t; i++) {
                    res1 = is_palindrom(text.sentences[i]);
                    if (res1 == 0) {
                        wprintf(L"Предложение №%d: Кто-то потерял все палиндромы.\n", i + 1);
                    }
                    if (res1 == 1) {
                        wprintf(L"Предложение №%d: Палиндромы на месте!\n", i + 1);
                    }
                    if (res1 == 2) {
                        wprintf(L"Предложение №%d: Чего-то не хватает.\n", i + 1);
                    }
                }
            }
                break;
            case 2:{
                for (i = 0; i < text.len_t; i++) {
                    text.sentences[i] = special_sym(text.sentences[i]);
                }
            }
                break;
            case 3:{
                qsort(text.sentences, text.len_t, sizeof(struct Sentence), sort_sent);
            }
                break;
            case 4: {
                for (i = 0; i < text.len_t; i++) {
                    res4 = delete_sent(text.sentences[i]);
                    if (res4) {
                        for (j = i; j < text.len_t; j++) {
                            text.sentences[j].sentence = text.sentences[j+1].sentence;
                            text.sentences[j].len_s = text.sentences[j+1].len_s;
                            text.sentences[j].count_w = text.sentences[j+1].count_w;
                            text.sentences[j].len_w = text.sentences[j+1].len_w;
                            text.sentences[j].words = text.sentences[j+1].words;
                        }
                        free(text.sentences[text.len_t].sentence);
                        for (j = 0; j < text.sentences[text.len_t].count_w; j++) {
                            free(text.sentences[text.len_t].words[j]);
                        }
                        free(text.sentences[text.len_t].words);
                        text.len_t -= 1;
                    }
                }
            }
                break;
            case 5:{
                for (i=0; i<text.len_t; i++) {
                    wprintf(L"%ls ", text.sentences[i].sentence);
                }
                wprintf(L"\n");
            }
            break;
            default:{
                wprintf(L"Данные некорректны.\n");
            }
            break;
        }
        wscanf(L"%d", &command);
    }
    for (i=0; i<text.len_t; i++){
        for (j=0; j<text.sentences[i].count_w; j++){
            free(text.sentences[i].words[j]);
        }
        free(text.sentences[i].sentence);
    }
    free(text.sentences);
    return 0;
}

