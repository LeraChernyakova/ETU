#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BASE_SIZE 50                        // "Базовый" размер динамически выделяемой памяти
#define LAST_SENTENCE "Dragon flew away!\n" // Последнее предложение текста
#define SPECIAL_COMBINATION "555"           // Комбинация символов, предложения содержащие которую должны быть удалены

char get_first_character();
char *get_sentence();
int get_text(char ***text);
int character_condition(char character);
int check_combination(char *sentence);
void delete_combination(char ***text, int *text_size);
void free_text(char ***text, int text_size);

int main() 
{
	char **text;
	int text_size = get_text(&text);
	int new_text_size = text_size;

	delete_combination(&text, &new_text_size);

	for (int i = 0; i < new_text_size; i++)
	{
		printf("%s", text[i]);
	}
	printf("Количество предложений до %d и количество предложений после %d\n", text_size-1, new_text_size-1);

	free_text(&text, new_text_size);

	return 0;
}

char get_first_character() 
{ // Возвращает первый найденный символ строки, при этом пропуская пробелы/табуляции/символы переноса строки
	char character;
	for (character = getchar(); character == ' ' || character == '\t' || character == '\n'; character = getchar()) {}
	
	return character;
}

char *get_sentence() 
{ // Получает следующее предложение из stdin, в случае неудачи возвращает NULL
	
	int str_size = BASE_SIZE;
	char *t = malloc(str_size*sizeof(char)); // Временная переменная для хранения адреса динамически выделяемой памяти

	if (t != NULL) 
	{
		char *sentence = t;
		char character = get_first_character();
		int i;

		for (i = 0; character != '.' && character != ';' && character != '?' && character != '!'; character = getchar()) 
		{	
			sentence[i++] = character;

			if (i == str_size-2) 
			{ // Условие необходимости выделения дополнительной памяти
			  // [a_0, a_1, a_2, ..., a_(str_size-2), a_(str_size-1), a_(str_size)]
			  //                                      ^'\n'           ^'\0'
				str_size += BASE_SIZE;
				t = realloc(sentence, str_size*sizeof(char));
				if (t != NULL) 
				{
					sentence = t;
				} else 
				{
					free(sentence);
					return NULL;
				}
			}
		}

		sentence[i++] = character; // Добавление символа, означающего окончание стороки ('.'/';'/'?'/'!') 
		sentence[i++] = '\n';      // Добавление символа переноса строки
		sentence[i] = '\0';        // Добавление символа конца строки

		return sentence;
	}
	return NULL;
}

int get_text(char ***text) 
{ // Записывает текст, получаемый из stdin, в text, возвращает количество считанных предложений;
  // В случае неудачи возвращает 0
	int text_size = BASE_SIZE;
	char **t = malloc(text_size*sizeof(char**)); // Временная переменная для хранения адреса динамически выделяемой памяти

	if (t != NULL) 
	{
		*text = t;
		char *sentence;
		int i = 0;

		for (sentence = get_sentence(); strcmp(sentence, LAST_SENTENCE) != 0; sentence = get_sentence()) 
		{	
			if (sentence == NULL) 
			{
				free_text(text, i);
				return 0;
			}

			(*text)[i++] = sentence;

			if (i == text_size) 
			{ // Условие необходимости выделения дополнительной памяти
				text_size += BASE_SIZE;
				t = realloc(t, text_size*sizeof(char**));
				if (t != NULL) 
				{
					(*text) = t;
				} else 
				{
					free_text(text, i);
					return 0;
				}
			}
		}
		
		(*text)[i++] = sentence;
		
		return i;
	}
	return 0;
}

int character_condition(char character) 
{ // Проверяет, является ли символ частью слова/числа
	if ((character < '0' || character > '9') && (character < 'A' || character > 'Z') && (character < 'a' || character > 'z')) 
	{
		return 1;
	}
	return 0;
}

int check_combination(char *sentence) 
{ // Проверяет, содержит ли предложение комбинацию символов SPECIAL_COMBINATION
	char *combination = SPECIAL_COMBINATION;
	int flag;

	for (int i = 0; i < strlen(sentence) - strlen(combination); i++) 
	{
		flag = 1;
		for (int j = 0; j < strlen(combination); j++) 
		{	
			if (sentence[i+j] != combination[j]) 
			{
				flag = 0;
				break;
			}
		}

		if (flag && ((i == 0 || character_condition(sentence[i-1])) && character_condition(sentence[i+strlen(combination)]))) 
		{ // Проверка, являются ли символы перед и после найденой комбинации частью слова/числа
			return 0;
		} 
	}
	return 1;
}

void delete_combination(char ***text, int *text_size) 
{ // Редактирует массив text, удаляя все предложения, содержащие комбинацию символов SPECIAL_COMBINATION

	char **t = malloc(*text_size*sizeof(char**)); // Временная переменная для хранения адреса динамически выделяемой памяти

	if (t != NULL) 
	{
		char **out = t; // Массив, в котором будут записаны предложения, не содержащие комбинацию SPECIAL_COMBINATION
		int k = 0;

		for (int i = 0; i < *text_size; i++) 
		{
			if (check_combination((*text)[i])) 
			{	
				out[k++] = (*text)[i]; // В случае, если предложение содержит комбинацию SPECIAL_COMBINATION, то предложение добавляется в out
			} else 
			{	
				free((*text)[i]);      // Иначе, память, выделенная под предложение, освобождается
			}
		}

		// Переписывание содержимого массива text
		free(*text);
		*text = out;
		*text_size = k;
	}
}

void free_text(char ***text, int text_size) 
{ // Освобождение памяти
	for (int i = 0; i < text_size; i++) {
		free((*text)[i]);
	}
	free(*text);
}
