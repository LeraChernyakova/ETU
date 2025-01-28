#include "print_dict.h"

int print_dict(struct Text text)
{
	int i=0, j=0, word_size=0, list_size = 1, flag = -1;
	wchar_t letter = L'1';
	wchar_t ** word_list;
	int * count_list;
	wchar_t * word;
	word_list = calloc(1, sizeof(wchar_t * ));
	count_list = calloc(1, sizeof(int));
	word = calloc(1, sizeof(wchar_t));
	for (int i=0; i<text.size_text; i++)
	{
		for (int j=0; j<text.list_sentences[i].size_sentence; j++)
		{
			letter =(wchar_t) text.list_sentences[i].sym_sentence[j];
			
			if (letter != ' ' && letter != '\n' && letter != '\t' && letter != ',' && letter != '.')
			{
				
				*(word + word_size) = letter;
				word_size++;
				word = realloc(word, (word_size+1) * sizeof(wchar_t));
			}
			else
			{
				if (word_size != 0)
				{
					*(word + word_size) = '\0';
					for (int k = 0; k < list_size-1; k++)
					{
						if (wcscmp(*(word_list+k), word) == 0)
							flag = k;
							
					}
					if (flag == -1)
					{
						*(word_list + list_size - 1) = calloc((word_size+1), sizeof(wchar_t));
						wcscpy(*(word_list + list_size - 1), word);
						*(count_list + list_size - 1) = 1;
						list_size++;
						word_list = realloc (word_list, list_size * sizeof(wchar_t * ));
						count_list = realloc (count_list, list_size * sizeof(int));
					}
					else
					{
						*(count_list + flag) = *(count_list + flag) + 1;
					}
					flag = -1;
					word_size = 0;
				}
			}
		}
	}
	for (i =0; i<list_size-1; i++)
		{
			wprintf(L"%ls ", *(word_list + i));
			wprintf(L"%d\n", *(count_list + i));
			free(*(word_list + i));
		}
	free(word_list);
	free(count_list);
	return 0;
}
