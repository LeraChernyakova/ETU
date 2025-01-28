#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "windows.h"

char input_string[81];
char result[161];

int main() {
	setlocale(LC_ALL, "Russian.1251");
	FILE* f;
	f = fopen("res.txt", "w");
	SetConsoleCP(1251);
	printf("Студентка - Чернякова Валерия.\nГруппа 1304.\nЗадание - преобразовать введенных во входной строке десятичных цифр в восьмеричную СС, остальные символы входной строки передаются в выходную строку непосредственно.\n");
	fgets(input_string, 81, stdin);
	input_string[strlen(input_string) - 1] = '\0';
	__asm {
		push ds
		pop es
		mov esi, offset input_string
		mov edi, offset result
		readout :
		lodsb
			cmp al, 56; сравниваем  с 8
			jne check; два числа не равны
			mov ax, '01'
			stosw; запись слова в строку
			jmp ongoing
			check :
		cmp al, '9'
			jne save_record
			mov ax, '11'
			stosw
			jmp ongoing
			save_record :
		stosb; запись байта в строку
			ongoing :
		cmp[esi], '\0'
			jne readout
	}
	printf("%s", result);
	fprintf(f, "%s", result);
	flose(f);
	return 0;
}