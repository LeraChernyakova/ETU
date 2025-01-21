#include "structs.h"
#include "get_text.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CIRILLIC_A 1040
#define CIRILLIC_ya 1103
#define CIRILLIC_YO 1025
#define CIRILLIC_yo 1105

#define BASE_SIZE 50

int get_text(struct Text* output)
{
	setlocale(LC_ALL, "");

	int buffer_size = BASE_SIZE;
	struct Sentence* buffer = malloc(buffer_size*sizeof(struct Sentence));

	if (buffer != NULL)
	{
		int i = 0;
		struct Sentence* temp_buffer;
		int eoi_detector = 0;

		do
		{
			eoi_detector = get_sentence(&buffer[i++]);

			if (eoi_detector < 0)
			{
				for (int k = 0; k < i-1; k++)
				{
					free(buffer[k].content);
				}
				free(buffer);
				return 1;
			}

			if (i >= buffer_size)
			{
				buffer_size += BASE_SIZE;
				temp_buffer = realloc(buffer, buffer_size*sizeof(struct Sentence));
				if (temp_buffer != NULL)
				{
					buffer = temp_buffer;
				} else
				{
					if (eoi_detector != 0) i--;

					for (int k = 0; k < i; k++)
					{
						free(buffer[k].content);
					}
					free(buffer);
					return 1;
				}
			}
		} while (eoi_detector == 0);

		output->content = buffer;
		output->size = --i;
		return 0;
	}
	return 1;
}

int get_sentence(struct Sentence* output)
{
	setlocale(LC_ALL, "");
	
	wchar_t* content;
	int out = get_content(&content);
	if (out)
	{
		return out;
	}

	output->content = content;
	output->number_of_cirillic_characters = cirillic_characters_counter(content);
	output->are_there_sp_symbols = sp_symbols_detector(content);
	output->size = wcslen(content);

	return out;
}

int get_content(wchar_t** string)
{
	setlocale(LC_ALL, "");

	int buffer_size = BASE_SIZE;
	wchar_t* buffer = malloc(buffer_size*sizeof(wchar_t));
	
	if (buffer != NULL)
	{
		int i = 0;
		wchar_t* temp_buffer;
		wchar_t character;
		int bn_contact = 0;

		do 
		{
			character = getwchar();
			buffer[i++] = character;
			
			if (character == '\n')
			{
				bn_contact++;
			} else
			{
				bn_contact = 0;
			}

			if (i >= buffer_size-1)
			{
				buffer_size += BASE_SIZE;
				temp_buffer = realloc(buffer, buffer_size*sizeof(wchar_t));
				
				if (temp_buffer != NULL)
				{
					buffer = temp_buffer;
				} else
				{
					free(buffer);
					return -1;
				}
			}
		} while (character != '.' && bn_contact < 2);

		if (bn_contact < 2) 
		{
			buffer[i] = '\0';
			remove_spaces(buffer);
			*string = buffer;
			return 0;
		} else
		{
			free(buffer);
			return 1;
		}
	}
	return -1;

}

void remove_spaces(wchar_t* string)
{
	setlocale(LC_ALL, "");

	int spaces_counter;
	for (spaces_counter = 0; iswspace(string[spaces_counter]); spaces_counter++);

	memmove(string, string+spaces_counter, (wcslen(string)-spaces_counter+1)*sizeof(wchar_t));
}

int sp_symbols_detector(wchar_t* string)
{
	setlocale(LC_ALL, "");
	
	for (int i = 0; string[i] != '.'; i++)
	{
		if (iswalnum(string[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int cirillic_characters_counter(wchar_t* string)
{
	setlocale(LC_ALL, "");
	
	int counter = 0;
	
	for (int i = 0; string[i]; i++)
	{
		if (string[i] >= CIRILLIC_A && string[i] <= CIRILLIC_ya || string[i] == CIRILLIC_YO || string[i] == CIRILLIC_yo)
		{
			counter++;
		}
	}
	return counter;
}
