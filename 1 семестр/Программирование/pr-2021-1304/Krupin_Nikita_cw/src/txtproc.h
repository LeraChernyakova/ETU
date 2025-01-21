#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#ifndef ___TXT_STRUCT___
    #define ___TXT_STRUCT___
    typedef struct Word{
		wchar_t* wchars;
		wchar_t sep;
		int size, len;
	} Word;
	typedef struct Sentence{
		Word* words;
		int size, len;
	} Sentence;
	typedef struct Text{
		Sentence* sents;
		int size, len;
	} Text;
#endif

int removeDuplicate(Text*);
void swapWordEnds(Text);
void findWord(int, int, Text);
int sentCmp(const void*, const void*);
int removeSents(Text*);
void removeSentence(int, Text*);
void freeSentence(Sentence);
void freeText(Text*);
