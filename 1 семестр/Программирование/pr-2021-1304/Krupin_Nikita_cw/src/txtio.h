#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define MEM_STEP 8
#define SENT_SEP L".\n"
#define WORD_SEP L" ,"

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

Word readWord();
Sentence readSentence();
Text readText();
void printText(Text);
