//  kursach.c

#include "top_header.h"
#include "read_text.h"
#include "primitiv_func.h"
#include "anagram.h"
#include "sort_upper.h"
#include "write.h"
#include "one_on_two_char.h"
#include "swap_word.h"


int main (){

    setlocale(LC_ALL,"");

    //объявление переменных
    Text _text,new_text ;
    int i,ans;
    wchar_t word_old[MAX_LEN_WORD],word_new[MAX_LEN_WORD];

    //считывание текста
    wprintf(L"Введите  текст (конец ввода два enter):\n");
    _text = read_text();

    while (1) {
        wprintf(L"Введите команду :\n\t"
                "1 - Анаграммы ;\n\t"
                "2 - Отсортировать предложения  по количеству заглавных букв в нем;\n\t"
                "3 - Заменить каждую гласную буквы двумя другими буквами идущими следующими по алфавиту;\n\t"
                "4 - Заменить одно слово  на другое во всем тексте ;\n\t"
                "5 - Ввести новый текст;\n\t"
                "6 - Вывести текущий текст;\n\t"
                "0 - Выход;\n");

        wscanf(L"%i", &ans);
        while ((getwchar ()) != '\n');//очистка буфера ввода

        switch (ans) {
            case 0 ://очистка
                for (i = 0; i < _text.size; i++) {
                    free(_text.sents[i].str);
                }
                free(_text.sents);

                return 0;

            case 1 :
                write(find_anagram(_text), 1);
                break;

            case 2 :
                new_text = sort_text_upper(_text);
                write(new_text, 2);
                for (i = 0; i < new_text.size; i++) {
                    free(new_text.sents[i].str);
                }
                free(new_text.sents);
                break;

            case 3 :
                _text = replace_substr(_text);
                write(_text, 3);
                break;

            case 4 :
                wprintf(L"\nВведите  слово которое хотите заменить:\n");
                fgetws(word_old,MAX_LEN_WORD,stdin);
                wprintf(L"\nВведите  слово НА которе  хотите заменить:\n");
                fgetws(word_new,MAX_LEN_WORD,stdin);

                delt_char((int)wcslen(word_old)-1,word_old);
                delt_char((int)wcslen(word_new)-1,word_new);

                for(i = 0; i < _text.size ;i++){
                    _text.sents[i] = find_and_swap_word(_text.sents[i],word_old,word_new);
                }
                write(_text, 4);

                break;

            case 5 :
                for (i = 0; i < _text.size; i++) {
                    free(_text.sents[i].str);
                }
                free(_text.sents);

                wprintf(L"\nВведите  текст (конец ввода два enter):\n");
                _text = read_text();
                break;

            case 6 :
                write(_text, 6);
                break;
                
            default:
		wprintf(L"\nНет такой команды , введите другую!\n");
		wprintf(L"Чтобы продолжить нажмите Enter:\n");
    		while ((getwchar ()) != '\n');
		break;
        }



    }



}
