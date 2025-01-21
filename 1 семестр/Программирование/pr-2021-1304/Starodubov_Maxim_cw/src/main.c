#include "structs.h"
#include "main_functionality.h"
#include "time_diffs.h"
#include "useful.h"
#include "get_text.h"
#include "colors.h"

int main()
{
	setlocale(LC_ALL, "");

	struct Text text;
	wprintf(L"Введите текст, для окончания ввода 2 раза нажмите 'Enter':\n");
	wprintf(L"%s", TEXT_INPUT);
	int error_detector = get_text(&text);
	wprintf(L"%s", NORMAL);

	if (error_detector != 0)
	{
		wprintf(L"%sПохоже, что введенный вами текст слишком большой, выполнение программы прервано.%s", DUNGER, NORMAL);
		return 0;
	}
	remove_duplicate(&text);

	wprintf(L"%s\tПри вводе команд просим Вас использовать только численные значения!%s\n%s\tВвод каких-либо символов при вводе команды может привести к печальным последствиям!%s\n\n", DUNGER, NORMAL, DUNGER, NORMAL);

	int command;

	do 
	{
		wprintf(L"%s\tКакое действие необходимо выполнить?\n%s1: Для каждой подстроки в тексте, задающей время вида “часы:минуты”, вывести номер\nпредложения в котором она встречается и количество минут до текущего времени.\n2: В каждом предложении удалить все заглавные латинские буквы.\n3: Отсортировать предложения по уменьшению количества кириллических букв.\n4: Удалить все предложения в которых нет специальных символов.\n5: Распечатать текст, разделяя предложения пробелаим.\n6: Распечатать текст, выводя каждое предложение на новой строке.\n7: Ввести новый текст.\nДля выхода введите '0'.\n", SUCCESS, NORMAL);
		wprintf(L">>> ");

		command = 0;
		wscanf(L"%d", &command);
		
		switch (command)
		{
			case 0:
				break;
			case 1:
				print_time_diffs(&text);
				break;
			case 2:
				remove_uppercase_latin(&text);
				output_request(&text);
				break;
			case 3:
				sort_by_cirillic(&text);
				output_request(&text);
				break;
			case 4:
				remove_special(&text);
				output_request(&text);
				break;
			case 5:
				print_text(&text, ' ');
				break;
			case 6:
				print_text(&text, '\n');
				break;
			case 7:
				free_text(&text);
				wprintf(L"Для окончания ввода 2 раза нажмите 'Enter':\n");
				wprintf(L"%s", TEXT_INPUT);
				error_detector = get_text(&text);
				wprintf(L"%s", NORMAL);
				if (error_detector != 0)
				{
					wprintf(L"%sПохоже, что введенный вами текст слишком большой, выполнение программы прервано.%s", DUNGER, NORMAL);
					return 0;
				}
				remove_duplicate(&text);
				break;
			default:
				wprintf(L"Такой команды не существует.\n");
		}

	} while (command);

	free_text(&text);
	return 0;
}
