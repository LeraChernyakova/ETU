#include <locale.h>
#include "txtio.h"
#include "txtproc.h"

#define BUFF_SIZE 256

int main()
{
	Text text; wchar_t ws[BUFF_SIZE] = L"";
	setlocale(LC_ALL, "");
	fputws(L"\033[0;33mРежим ввода. Введите текст одной строкой.\n", stdout);
	fputws(L"Разделитель предложений - точка.\n", stdout);
	fputws(L"Разделитель слов - пробел или запятая.\033[0m\n", stdout);
	text = readText();
	fputws(L"\033[0;32mПовторяющиеся предложения удалены: ", stdout);
	wprintf(L"%d\033[0m\n", removeDuplicate(&text));
	printText(text);
	while (ws[0] != L'5'){
		fputws(L"\033[0;33mРежим обработки текста. Выберите действие:\n", stdout);
		fputws(L"1 - поменять окончания \"тся\"-\"ться\";\n", stdout);
		fputws(L"2 - найти второе слово первого предложения;\n", stdout);
		fputws(L"3 - сортировать предложения по возрастанию количества слов;\n", stdout);
		fputws(L"4 - удалить предложения, в которых больше 10 слов;\n", stdout);
		fputws(L"5 - завершить обработку.\033[0m\n", stdout);
		fgetws(ws, BUFF_SIZE, stdin);
		switch (ws[0]){
			case L'1':
				fputws(L"\033[0;32m1. Результат замены на экране:\033[0m\n", stdout);
				swapWordEnds(text);
				printText(text);
				break;
			case L'2':
				fputws(L"\033[0;32m2. Результат поиска на экране:\033[0m\n", stdout);
				findWord(0, 1, text);
				break;
			case L'3':
				fputws(L"\033[0;32m3. Результат сортировки на экране:\033[0m\n", stdout);
				qsort(text.sents, text.len, sizeof(Sentence), sentCmp);
				printText(text);
				break;
			case L'4':
				fputws(L"\033[0;32m4. Результат на экране. Удалено предложений: ", stdout);
				wprintf(L"%d\033[0m\n", removeSents(&text));
				printText(text);
				break;
			case L'5':
				fputws(L"\033[0;32m5. Обработка завершена. Результат на экране:\033[0m\n", stdout);
				printText(text);
				break;
			default:
				fputws(L"\033[0;31mНекорректный номер действия, введите число от 1 до 5.\033[0m\n", stdout);
		}
	}
	freeText(&text);
	return 0;
}
