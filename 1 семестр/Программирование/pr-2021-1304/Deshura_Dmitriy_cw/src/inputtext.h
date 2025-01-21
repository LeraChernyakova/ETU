
#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>
#include"formattext.h"

#ifndef __Structs__
	#define __Structs__
	struct Sentence{
		wchar_t* str;
		int words_number;
	};

	struct Text{
		struct Sentence *sentences;
		int sents_number;
	};
#endif

wchar_t** input_text(int *c);

struct Sentence* make_sentences(int n, wchar_t **text_string, int* p);

