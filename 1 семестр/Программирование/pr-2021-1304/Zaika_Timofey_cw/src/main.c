#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEM_STEP 100
#define CRASH_MEMORY_MSG L"Ошибка выделения памяти"

#include <wchar.h>
#include <locale.h>

#include "textio.h"
#include "all_funcs.h"

int main(){
	setlocale(LC_ALL, "");
	wprintf(L"%ls\n", L"Приветствую!\n\nДанная программа обрабатывает введенный вами текст.\nТребования к тексту:\n\n1. Текст представляет собой предложения, разделенные точкой. Предложения - набор слов, разделенные пробелом или запятой, слова - набор латинских или кириллических букв, цифр и других символов кроме точки, пробела или запятой.\n2. Для выхода из ввода текста необходимо дважды нажать клавишу Enter.\n\nПосле ввода текста автоматически удаляются повторяющиеся предложения.\nПожалуйста, введите текст:");
	struct Text text = readText();

	changed_text(&text);
	wprintf(L"%ls\n", L"Ваш текст после удаления повторяющихся предложений:");
	print_text(&text);

	wprintf(L"%ls\n", L"");

	wprintf(L"%ls\n", L"Режим работы с текстом\nКакое действие с текстом вы хотите выполнить?");
	wprintf(L"%ls\n", L"Введите номер команды:\n1. Распечатать каждое слово которое встречается не более одного раза в тексте.\n2. Каждую подстроку в тексте имеющую вид “<день> <месяц> <год> г.” заменить на подстроку вида “ДД/ММ/ГГГГ” (аналогично для английского языка).\n3. Отсортировать предложения по произведению длин слов в предложении.\n4. Удалить все предложения, которые содержат символ ‘#’ или ‘№’, но не содержат ни одной цифры.\n0. Выход из программы");
	wprintf(L"%ls", L">");

	wchar_t command = getwchar();
	switch(command){
		case L'0':
			free_text(&text); 
			return 0;
		case L'1':
			wprintf(L"%ls\n", L"Результат работы функции:");
			single_word(&text);
			break;
		case L'2': 
			change_date(&text);
			wprintf(L"%ls\n", L"Результат работы функции:");
			print_text(&text);
			break;
		case L'3':
			sort_sents(&text);
			wprintf(L"%ls\n", L"Результат работы функции:");
			print_text(&text);
			break;
		case L'4': 
			remove_symbols(&text);
			wprintf(L"%ls\n", L"Результат работы функции:");
			print_text(&text);
			break;
		default: 
			wprintf(L"%ls\n", L"Неверно введена команда!");
			break;

	free_text(&text);
	return 0;
	}
}
