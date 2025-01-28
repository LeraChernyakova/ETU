#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "consts.h"
#include "string_structures.h"
#include "substring_struct.h"
#include "functions_for_sentence.h"
#include "functions_for_text.h"
#include "string_functions.h"

void print_menu(void);

int main() {
    setlocale(LC_ALL, "");
    struct Text processed_text;
    int user_request;
    int i, j;
    struct Substrings answer;
    int is_correct;
    get_text(&processed_text);
    get_words(&processed_text);
    wchar_t current_symbol;
    int is_find;

    // вывод меню

    for (;;){
        // запрос от пользователя
        print_menu();
        user_request = 0;
        wscanf(L"%d", &user_request);
        while ((current_symbol = getwchar()) != '\n');
        if (user_request == 5){
            free_memory(&processed_text);
            return 0;
        }

        switch (user_request){
            case 1:
                is_find = 0;
                get_substrings(&answer, &processed_text);
                for (i = 0; i < answer.num_words; i++){
                    if (answer.num_occur[i] > 2){
                        is_find = 1;
                        wprintf(L"%ls %d\n", answer.words[i], answer.num_occur[i]);
                    }
                    free(answer.words[i]);
                }
                free(answer.words);
                free(answer.num_occur);
                if (!is_find){
                    wprintf(L"По Вашему запросу ничего не найдено.");
                }
                break;
            case 2:
                replace_digits(&processed_text);
                print_text(&processed_text);
                break;
            case 3:
                for (i = 0; i < processed_text.text_len; i++){
                    for (j = 0; j < processed_text.sentences[i].words_number; j++){
                        processed_text.sentences[i].words[j].number_of_latin_letters = get_number_of_latin_letters(processed_text.sentences[i].words[j]);
                    }
                }

                sort_words(&processed_text);
                print_text(&processed_text);
                break;
            case 4:
                set_k(&processed_text);
                print_text(&processed_text);
                break;
            default:
                wprintf(L"Неизвестная команда.\n");   
                break;
        }
    }

    return 0;
}

void print_menu(void){
    wprintf(L"\n\nВыберите функцию обработки текста:\n");
    wprintf(L"1 - вывод всех слов, встречающихся в тексте более двух раз\n");
    wprintf(L"2 - замена всех цифр на число их вхождений\n");
    wprintf(L"3 - сортировка слов в предложениях по числу латинских букв в них\n");
    wprintf(L"4 - изменить порядок слов на обратный в предложениях, состоящих только из кириллических букв\n");
    wprintf(L"5 - выход\n");
}

