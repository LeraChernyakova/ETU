#include "pch.h"
#include <iostream>
#include <stdio.h>

#define N 80
#define T 0
using namespace std;

int main()
{
	system("chcp 1251 > nul");
	char _str[N + 1];
	char msg[] = "ЛР4. Ларин Антон 8383. 13) Формирование номера введенной русской буквы по алфавиту и номера позиции его первого вхождения во входной строке и выдача их на экран.\n";
	cout << msg;
	int i = 0;
	char alphaNum=-1;
	int firstOcc=-1;
	cin.getline(_str, N);
	_asm {
		sub eax, eax;
		mov al, T;	al <- termenate symbol
		mov ecx,N;	
		lea edi,_str;
		repne scas; cmps;
		sub ecx, N;
		not ecx;	ecx < -length(_str)
		mov edx, ecx; edx <- ecx (length)
		sub edi,edi

	cycle:
		mov edi, edx;	edi <- current index defined by counter
		sub edi, ecx;

		mov al, _str[edi];	al <- current symbol

		cmp al, 'Ё';	Self-explanatory
		je isYo;
		cmp al, 'ё';
		je isYo;

		cmp al, 'А';	In bounds. Otherwise - not cyrilic
		jl notCyrilic;
		cmp al, 'я';
		jg notCyrilic;
	isCyrilic:
		mov firstOcc, edi;	firstOcc <- current sybmol index (first cyrilic occurance)
			cmp al, 'а';	а+ are lower, Я- are upper
		jge isLower;
	isUpper:
		cmp al, 'Е';
		jle beforeYo;
		inc al;	Letters after ё are one position bigger
	beforeYo:
		sub al, 'А';	Get alphabetical position
		inc al;			Muggles are counting from one
		mov alphaNum, al; alphaNum <-alphabetical position
		jmp hooray;	Thie end
	isLower:
		cmp al, 'е';
		jle beforeYo_;
		inc al;
	beforeYo_:
		sub al, 'а';
		inc al;
		mov alphaNum, al;
		jmp hooray;
	isYo:;Dё yёё rёmёmbёr mё?
		mov alphaNum, 7; Truly magic number
		mov firstOcc, edi;
		jmp hooray;
	notCyrilic:
		loop cycle;
	hooray:
	}
	if (firstOcc != -1) {
		cout << "Первое вхождение русского символа: " << firstOcc << endl;
		cout << "Номер по алфавиту: " << (int)alphaNum<< endl;;
	}
	else {
		cout << "Русских букв нет" << endl;
	}
	return 0;
}