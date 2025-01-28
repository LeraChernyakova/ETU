#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <stdlib.h>
#include "structs.h"
#include "text_func.h"
#include "double_letters.h"
#include "q_sort.h"
#include "replace.h"
#include "set_color.h"
#include "text_func.h"

int main() {
    setlocale(LC_ALL, "");
    wchar_t command = L'0', space;
    struct Text inp_text;
    wprintf(L"Введите текст\n");
    inp_text = get_text();
    wprintf(L"Выберете команду:\n"
            "1: В каждом предложении заменить первое слово на второе слово из предыдущего.\n"
            "2: Отсортировать предложения по длине третьего слова.\n"
            "3: Вывести на экран текст, выделяя зеленым слова, в середине которых есть цифры.\n"
            "4: Убрать в словах повторяющиеся символы.\n"
            "5: Вывести текст на экран.\n"
            "6: Выйти из редактора текста.\n");
    while (command != L'6'){
        command = getwchar();
        space = getwchar();
        switch(command){
            case L'1': {
                replace(inp_text);
                break;
            }
            case L'2': {
                q_sort(inp_text);
                break;
            }
            case L'3': {
                set_color(inp_text);
                break;
            }
            case L'4': {
                double_letters(inp_text);
                break;
            }
            case L'5': {
                print_text(inp_text);
                break;
            }
            case L'6': {
                for (int i = 0; i < inp_text.len_text; i++){
                    free(inp_text.sentences[i].words);
                    free(inp_text.sentences[i].separator);
                }
                free(inp_text.sentences);
                break;
            }
            default:{
                wprintf(L"Данной опции не существует\n");
                break;
            }
        }
    }
    return 0;
}
