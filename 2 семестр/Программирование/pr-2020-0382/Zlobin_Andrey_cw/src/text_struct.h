#pragma once

struct Sentence
{
	wchar_t * sym_sentence;
	int size_sentence;
	int is_end;
}; 

struct Text
{
	struct Sentence * list_sentences;
	int size_text;
};
