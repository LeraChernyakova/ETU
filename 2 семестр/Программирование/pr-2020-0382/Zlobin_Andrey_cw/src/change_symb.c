#include "change_symb.h"

struct Text change_symb(struct Text text)
{
	wchar_t * new_sentence;
	wchar_t buffer[5];
	int new_size=0;
	int counter=0, code = 0;
	int i=0, j=0, k=0, x=0;
	for (i=0; i<text.size_text; i++)
	{
		for (j=0; j<text.list_sentences[i].size_sentence; j++)
		{
			if (iswalpha(text.list_sentences[i].sym_sentence[j]))
				counter++;
		}
		new_size = text.list_sentences[i].size_sentence + (text.list_sentences[i].size_sentence - counter) * SYM_SIZE;
		new_sentence = malloc(new_size * sizeof(wchar_t));
		j= 0;
		
		while (text.list_sentences[i].sym_sentence[j] != '\0')
		{
			if (iswalpha(text.list_sentences[i].sym_sentence[j]))
			{
				
				new_sentence[k] = text.list_sentences[i].sym_sentence[j];
				k++;
			}
			else
			{
				for (x=0; x<SYM_SIZE; x++)
					buffer[x] = L'0';
				code = (int) text.list_sentences[i].sym_sentence[j];
				x=SYM_SIZE - 1;
				while (code!=0)
				{
					buffer[x] = L'0' + code % 10;
					code = code / 10;
					x--;
				}
				x = 0;
				for (x=0; x<SYM_SIZE; x++)
				{
					new_sentence[k] = buffer[x];
					k++;
				}
				x = 0;
			}
			
				j++;
			
		}
		new_sentence[k] = '\0';
		k=0;
		j=0;
		free(text.list_sentences[i].sym_sentence);
		text.list_sentences[i].sym_sentence = new_sentence;
		new_sentence = NULL;
		counter = 0;
	}
	return text;
}
