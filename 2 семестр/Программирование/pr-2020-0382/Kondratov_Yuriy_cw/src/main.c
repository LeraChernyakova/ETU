#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#include "output_funcs.h"
#include "processing_funcs.h"
#include "read_funcs.h"
#include "structures.h"

#define RESET_C L"\033[0m"
#define RED L"\033[1;91m"
#define TRUE 1

void print_menu();

int main() {
    setlocale(LC_ALL, "");

    print_menu();
    
    struct Text text;
	wprintf(L"Введите текст, который хотите обработать: \n");
    text = get_text();
    fgetwc(stdin);
    
    int option;
    int exit;
    while (TRUE){
    	wprintf(L"Пожалуйста, введите номер желаемой опции обработки текста:");
   		wscanf(L"%d", &option);
   		fgetwc(stdin);
   		switch (option) {
        	case 1:
        	    for (int i = 0; i < text.text_len; i++) {
        	        put_printed_sent(text.sentences[i]);
        	    }
        	    wprintf(L"\n");
        	    break;
        	case 2:
        	    for (int i = 1; i < text.text_len + 1; i++) {
        	        wprintf(L"В предложении %d:", i);
        	        if (!put_start_end_upper_words(text.sentences[i])){
        	        	wprintf(RED L" подходящих слов не нашлось." RESET_C);
        	        }
        	        wprintf(L"\n");
        	    }
        	    break;
        	case 3:
        	    qsort(text.sentences, text.text_len, sizeof(struct Sentence), last_words_cmp);
        	    for (int i = 0; i < text.text_len; i++) {
        	        fputws(text.sentences[i].first_word, stdout);
        	        wprintf(L"\n");
        	    }
        	    break;
        	case 4:
        	    for (int i = 0; i < text.text_len; i++) {
        	        put_sent_without_numbers(text.sentences[i]);
        	    }
        	    wprintf(L"\n");
        	    break;
        	default:
        	    wprintf(L"Неверно введён номер опции.\n");
    	}
    	wprintf(L"Пожалуйста, введите 1 для выбора другой опции обработки или 0 для выхода из программы:");
    	wscanf(L"%d", &exit);
    	if (!exit) break;
    }
    
    for (int i = 0; i < text.text_len; i++) {
        free(text.sentences[i].sentence);
        free(text.sentences[i].sent_copy);
        free(text.sentences[i].words);
    }
    free(text.sentences);
    
    return 0;
}

void print_menu(){
	wprintf(L"Уважаемый пользователь, вас приветствует программа обработки текста!\n"\
    "Возможны следующие опции обработки текста:\n"\
    "1) Раскрасить текст.\n2) Вывести слова, начинающиеся и заканчивающиеся на заглавную букву.\n"\
    "3) Отсортировать предложения по длине последнего слова в предложении.\n"\
    "4) Удалить все числа из предложений.\n");
}



