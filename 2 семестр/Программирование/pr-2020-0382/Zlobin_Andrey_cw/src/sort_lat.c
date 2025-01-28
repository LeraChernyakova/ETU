#include "sort_lat.h"

int compare_sentences(const void * s1, const void * s2)
{
	int i=0, counter1 = 0, counter2 = 0;
	struct Sentence sent1;
	struct Sentence sent2;
	sent1 = *(struct Sentence * ) s1;
	sent2 = *(struct Sentence * ) s2;
	for(i=0; i<sent1.size_sentence; i++)
	{
		if ((sent1.sym_sentence[i] >= L'A' && sent1.sym_sentence[i] <= L'Z') ||(sent1.sym_sentence[i] >= L'a' && sent1.sym_sentence[i] <= L'z'))
			counter1++;
	}
	for(i=0; i<sent2.size_sentence; i++)
	{
		if ((sent2.sym_sentence[i] >= L'A' && sent2.sym_sentence[i] <= L'Z') ||(sent2.sym_sentence[i] >= L'a' && sent2.sym_sentence[i] <= L'z'))
			counter2++;
		
	}
	return (counter1 - counter2);
}

struct Text sort_lat(struct Text text)
{
	qsort(text.list_sentences, text.size_text, sizeof(struct Sentence), compare_sentences);
	return text;
}
