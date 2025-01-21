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

void delete_lat_and_kir(struct Text * text);


int funcmp( const void * val1, const void * val2 );


void replace(struct Text *text);

 
void palindroms(struct Text* text);
 
 
void remove_repetes(struct Text* text);

