#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<wctype.h>
#include<ctype.h>

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

struct Text command_1 (struct Text text);

struct Text command_2 (struct Text text);

void command_3 (struct Text text);

struct Text command_4(struct Text text);

wchar_t* slice(wchar_t* str, int start, int end);

wchar_t* wstr_tolower( wchar_t* first_str);

wchar_t* get_second_word(struct Text text, int index);

int compare(const void* sent1, const void* sent2);

int numbers_inside(wchar_t *str);

struct Sentence *delete_repeated_sentences(struct Sentence *sentences, int *p);

void input_text_free(int n, wchar_t** text_string);
