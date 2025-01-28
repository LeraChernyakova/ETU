#include "input.h"

struct Sentence get_sentence() {
	struct Sentence new_sentence;
	int sent_mem_size = 1;
	int is_end = 0;
	int begin = 1;

	new_sentence.sym_sentence = calloc(sent_mem_size, sizeof(wchar_t));

	wchar_t letter;
	wchar_t prev_letter = L'1';
	do {
		letter = (wchar_t) fgetwc(stdin);
		if (letter == L'\n' && prev_letter == L'\n')
		{
			is_end = 1;
			break;
		}
		if ((letter == L'\t' || letter == L'\n' || letter == L' ') && begin == 1)
        		begin = 1;
        	else
        	{
        		begin = 0;
			new_sentence.sym_sentence[sent_mem_size-1] = letter;
			sent_mem_size++;
			new_sentence.sym_sentence =realloc(new_sentence.sym_sentence, sent_mem_size * (sizeof(wchar_t)));
        	}
		prev_letter = letter;
	} while (letter != L'.');
	new_sentence.sym_sentence[sent_mem_size-1] = L'\0';

	new_sentence.size_sentence = sent_mem_size - 1;
	new_sentence.is_end = is_end;
	return new_sentence;
}

struct Text get_text() {
	int text_mem_size = 1;
	struct Text text;
	int text_len = 0;
	int i;
	int flag = 1;
	text.list_sentences = calloc(text_mem_size, sizeof(struct Sentence));

	while (1)
	{
		struct Sentence sentence = get_sentence();
		for (i = 0; i < text_len; i++)
		{
			if (wcscasecmp(text.list_sentences[i].sym_sentence, sentence.sym_sentence)==0)
				flag = 0;
		}

		if (sentence.is_end)
			break;
		if (flag)
		{
			text.list_sentences[text_len++] = sentence;
			text_mem_size++;
			text.list_sentences = realloc(text.list_sentences, text_mem_size * (sizeof(struct Sentence)));
		}
		flag = 1;
	}

	text.size_text = text_len;
	return text;
}
