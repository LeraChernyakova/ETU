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
	f = fopen("Result.txt", "w");
	SetConsoleCP(1251);
	printf("Студентка - Чернякова Валерия.\nГруппа 1304.\nЗадание - преобразовать введенные во входной строке десятичные цифры в восьме-ричную СС, остальные символы входной строки передаются в выходную строку непосредственно.\n");
	fgets(input_string, 81, stdin);
	input_string[strlen(input_string) - 1] = '\0';
	__asm {
		push ds; save in stack ds
		pop es; es = ds, stack free  
		mov esi, offset input_string; source index - input string
		mov edi, offset result; receiver index – result string
		Reading :
			lodsb; loading a string operand into al, reading a symbol
			cmp al, 56; compare with code of number '8'
			jne CheckNine;
			mov al, ' '; move space in al
			stosb; save al by es : (e)di
			mov ax, '01'; move ax ‘01’, 8 in 8 number system
			stosw; 
			mov al, ' '; move space in al
			stosb; save al by es : (e)di
			jmp Final; unconditional transition by label Final
		CheckNine :
			cmp al, 57; compare with code of number '9'
			jne SaveRecord; transition by label SaveRecord, if al code not '9'
			mov al, ' '; move space in al
			stosb; save al by es : (e)di
			mov ax, '11'; move ax ‘11’, 9 in 8 number system
			stosw; save ax by es : (e)di
			mov al, ' '; move space in al
			stosb; save al by es : (e)di
			jmp Final; 
		SaveRecord :
			stosb; save al by es : (e)di
		Final :
			cmp[esi], '\0'; 
			jne Reading; last symbol esi != ‘\0’, then Reading
			stosb; save \0
	}
	printf("Результат работы программы:\n");
	printf("%s", result);
	fprintf(f, "%s", result);
	fclose(f);
	return 0;
}
