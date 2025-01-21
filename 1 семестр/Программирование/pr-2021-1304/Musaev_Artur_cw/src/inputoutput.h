#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#ifndef Structurs
#define Structurs
struct Sentence{
	wchar_t *str;
	int size;
};
 
 
struct Text{
	struct Sentence **sents;
	int size;
};
#endif


struct Text readText();

 
void output(struct Text* text);
