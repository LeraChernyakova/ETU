#include "del_sent_spec.h"

struct Text del_sent_spec(struct Text text)
{
	int i = 0, j = 0, k = 0;
	int flag_spec = 0, flag_up = 0;
	wchar_t letter;
	struct Sentence * new_list;
	
	new_list = calloc(text.size_text, sizeof(struct Sentence));
	
	
	for (i=0; i<text.size_text; i++)
	{
		for (j = 0; j < text.list_sentences[i].size_sentence; j++)
		{
			letter = text.list_sentences[i].sym_sentence[j];
			if (!(iswalpha(letter) || iswdigit(letter)) && letter != ' ' && letter != ',' && letter != '.')
				flag_spec = 1;
			if (iswupper(letter))
				flag_up = 1;
		}
		if (!(flag_spec && !flag_up))
		{
			
			*(new_list + k) = text.list_sentences[i];
			k++;
		}
		else
		{
			free(text.list_sentences[i].sym_sentence);
		}
		flag_spec = 0;
		flag_up = 0;
		
	}
	free(text.list_sentences);
	text.list_sentences = new_list;
	text.size_text = k;
	return text;
}

