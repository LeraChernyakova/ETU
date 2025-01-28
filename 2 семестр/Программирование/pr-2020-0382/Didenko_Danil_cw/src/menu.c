#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#include "structs.h"
#include "task_1.h"
#include "task_2.h"
#include "task_3.h"
#include "task_4.h"
#include "Input.h"


int main(){
    setlocale(LC_ALL,"");
    int i;
    Text text;
    wprintf(L"Введите текст:\n");
    get_text(&text);

    wprintf(L"Выберите задачу, которую нужно выполнить: \n"
            "1.Для каждого предложения вывести строку образец удовлетворяющую каждому слову в предложении.\n"
            "2.Удалить все предложения, в которых нет заглавных букв в начале слова.\n"
            "3.Отсортировать слова в предложении по количеству гласных букв в слове.\n"
            "4.Для каждого предложения вывести количество одинаковых слов в строке.\n"
            "5.Выход.\n");
    wchar_t input = getwchar();
    while (input != '5'){
        switch (input) {
            case '1'://общий шаблон для всех слов в предложении
                for (i = 0; i < text.count_sent; i++) {
                    task_1(&text.text[i]);
                    wprintf(L"%ls\n", text.text[i].sent);
                    wprintf(L"Подходящие шаблоны для слов предложения: ");
                    for (int p = 0; p < text.text[i].count_mask; p++) {
                        wprintf(L"%ls ", text.text[i].masks[p]);
                    }
                    if(text.text[i].count_words == 1){
                    	wprintf(L"%ls",text.text[i].words[0].word);
                    }else if(text.text[i].count_mask == 0){
                        wprintf(L"*?*");
                    }
                    
                    wprintf(L"\n");
                }
                wprintf(L"Следующее действие: ");
                break;
            case '2'://Удаляет из текста предложения , в которых слова начинаются с маленьких букв
                task_2(&text);
                for (i = 0; i < text.count_sent; i++) {
                    wprintf(L"%ls\n", text.text[i].sent);
                }
                wprintf(L"Следующее действие: ");
                break;
            case '3'://Сортирует по неубыванию слова в предложениях по количеству гласных.
                task_3(&text);
                for (i = 0; i < text.count_sent; i++) {
                    for (int j = 0; j < text.text[i].count_words-1; j++) {
                        wprintf(L"%ls ", text.text[i].words[j].word);
                    }
                    wprintf(L"%ls.\n", text.text[i].words[text.text[i].count_words-1].word);
                }
                wprintf(L"Следующее действие: ");
                break;
            case '4'://Выводит количество повторяющихся слов в предложении
                task_4(&text);
                for (i = 0; i < text.count_sent; i++) {
                    int count_print = 0;
                    wprintf(L"%ls\n", text.text[i].sent);
                    for (int j = 0; j < text.text[i].count_words; j++) {
                        if (text.text[i].words[j].is_first_rep == 1 && text.text[i].words[j].count_equal_words != 1) {
                            wprintf(L"%ls: %d.\n", text.text[i].words[j].word, text.text[i].words[j].count_equal_words);
                            count_print++;
                        }
                        if (j == text.text[i].count_words - 1 && count_print == 0) {
                            wprintf(L"Повторяющихся слов нет.\n");
                        }
                    }
                }
                wprintf(L"Следующее действие: ");
                break;
            case '\n':case' ': break;
            default:
                wprintf(L"Такой задачи не существует. Выберите другое действие: ");
        }
        input = getwchar();
        wprintf(L"\n");
    }
    wprintf(L"До свидания!\n");
    for (i = text.count_sent; i > 0;i--){
        for(int j = 0; j < text.text[i].count_mask;j++){
            free(text.text[i].masks[j]);
        }
        free(text.text[i].masks);
        free(text.text[i].sent);
        free(text.text[i].copy_sent);
        free(text.text[i].words);

    }
    free(text.text);
    return 0;
}
