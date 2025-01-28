#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>

#include "text_struct.h"
#include "input.h"
#include "print_dict.h"
#include "change_symb.h"
#include "sort_lat.h"
#include "del_sent_spec.h"



int main()
{
	setlocale(LC_ALL, "");
	struct Text new_text;
	int size;
	int edited_size;
	int i, n = -1;
	wchar_t sym;
	
	wprintf(L"%s\n", "Введите текст, который необходимо обработать:");
	new_text = get_text();
	
	
	
	while (n)
	{	
		wprintf(L"%s\n", "Для выбора варианта обработки нажмите нужную цифру:");
		wprintf(L"%s\n", "1 - Распечатать каждое слово и количество его повторений в тексте.");
		wprintf(L"%s\n", "2 - Заменить каждый символ, который не является буквой, на его код.");
		wprintf(L"%s\n", "3 - Отсортировать предложения по количеству латинских букв в предложении.");
		wprintf(L"%s\n", "4 - Удалить все предложения, которые содержат специальные символы и не содержат заглавные буквы.");
		wprintf(L"%s\n", "Чтобы вывести текущее состояние текста нажмите 5");
		wprintf(L"%s\n", "Для завершения работы программы нажмите 0");
		wscanf(L"%d", &n);
		switch (n)
		{
			case 0:
				for (i=0; i<new_text.size_text; i++)
					free(new_text.list_sentences[i].sym_sentence);
				free(new_text.list_sentences);
				return 0;
				break;
			case 1:
				print_dict(new_text);
				break;
			case 2:
				new_text = change_symb(new_text);
				break;
			case 3:
				new_text = sort_lat(new_text);
				break;
			case 4:
				new_text = del_sent_spec(new_text);
				break;
			case 5:
				for (i = 0; i <= new_text.size_text-1; i++)
				{
					wprintf(L"%ls\n", new_text.list_sentences[i].sym_sentence);
				}
				wprintf(L"\n");
				break;
			     default:
			     		wprintf(L"%ls\n", L"Введена неправильная команда, попробуйте ещё раз:");
		}
		
	}
	
	
	
	
	
	
	
	
	for (int j=0;j<new_text.size_text;j++)
		free(new_text.list_sentences[i].sym_sentence);
	free(new_text.list_sentences);
	return 0;
}
