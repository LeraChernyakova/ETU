#include "structs.h"
#include "main_functionality.h"
#include <stdlib.h>
#include <string.h>

void remove_duplicate(struct Text* text)
{
	setlocale(LC_ALL, "");

	int i = 0;
	int j = i + 1;
	struct Sentence* first_sentence;
	struct Sentence* second_sentence;

	while (i < text->size-1)
	{
		first_sentence = &text->content[i];
		while (j < text->size)
		{
			second_sentence = &text->content[j];
			if (wcscasecmp(first_sentence->content, second_sentence->content) == 0)
			{
				free(second_sentence->content);
				memmove(second_sentence, (second_sentence+1), (text->size-j+1)*sizeof(struct Sentence));
				text->size -= 1;
			} else
			{
				j++;
			}
		}
		i++;
		j = i + 1;
	}
}

void remove_uppercase_latin(struct Text* text)
{
	setlocale(LC_ALL, "");

	int j;
	struct Sentence* sentence;

	for (int i = 0; i < text->size; i++)
	{
		j = 0;
		sentence = &text->content[i];
		while (j < sentence->size)
		{
			if (sentence->content[j] >= 'A' && sentence->content[j] <= 'Z')
			{
				memmove(&sentence->content[j], &sentence->content[j+1], (sentence->size-j+1)*sizeof(wchar_t));
				sentence->size -= 1;
			} else
			{
				j++;
			}
		}
	}
}

void sort_by_cirillic(struct Text* text)
{
	setlocale(LC_ALL, "");

	qsort(text->content, text->size, sizeof(struct Sentence), compare);
}

int compare(const void* a, const void* b)
{
	setlocale(LC_ALL, "");

	struct Sentence* first_sentence = (struct Sentence*) a;
	struct Sentence* second_sentence = (struct Sentence*) b;

	if (first_sentence->number_of_cirillic_characters < second_sentence->number_of_cirillic_characters)
	{
		return 1;
	} else if (first_sentence->number_of_cirillic_characters > second_sentence->number_of_cirillic_characters)
	{
		return -1;
	}
	return 0;
}

void remove_special(struct Text* text)
{
	setlocale(LC_ALL, "");

	struct Sentence* sentence;

	int i = 0;
	while (i < text->size)
	{
		sentence = &text->content[i];
		if (sentence->are_there_sp_symbols == 0)
		{
			free(sentence->content);
			memmove(sentence, (sentence+1), (text->size-i+1)*sizeof(struct Sentence));
			text->size -= 1;
		} else 
		{
			i++;
		}
	}	
}
