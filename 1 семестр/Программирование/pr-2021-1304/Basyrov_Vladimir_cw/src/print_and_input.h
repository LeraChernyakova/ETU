#pragma once
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#define Size 50
#ifndef __Structs__
	#define __Structs__
	struct sentense{
		wchar_t *str;
		int kol;
		int *word;
		int kol_word;};

	struct text{
		struct sentense **sen;
		int kol_sen;
		int kol_sym;};
#endif
int * strtok_for_you(struct sentense *sen);
struct sentense* readsen();
struct text readtext();
void printText(struct text t);
