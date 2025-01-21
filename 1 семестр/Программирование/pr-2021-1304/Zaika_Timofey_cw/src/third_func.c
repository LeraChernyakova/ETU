#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEM_STEP 100
#define CRASH_MEMORY_MSG L"Ошибка выделения памяти"

#include <wchar.h>
#include <locale.h>

#include "textio.h"

int count_prod(struct Sentence *sentence){
	wchar_t sep[10] = L" ,!?;\n";
	wchar_t **word_sent = malloc(MEM_STEP*sizeof(wchar_t*));
	if(!word_sent){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
	int count_elem = 0;

	wchar_t *cur_sent = sentence->str;
	wchar_t temp_sent[wcslen(cur_sent)];
	wcscpy(temp_sent, cur_sent);

	wchar_t *istr;
	wchar_t *pwc;
	istr = wcstok(temp_sent, sep, &pwc);
	while(istr != NULL){
		wchar_t *temp = malloc(sizeof(wchar_t*));
		if(!temp){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
		wcscpy(temp, istr);
		word_sent[count_elem] = temp;
		count_elem++;
		istr = wcstok(NULL, sep, &pwc);
	}

	int cur_prod = 1;

	for(int i=0; i<count_elem; i++){
		int temp_count_words = 0;
		for(int j=0; j<wcslen(word_sent[i]); j++){
			temp_count_words++;
		}
		if(temp_count_words != 0){
			cur_prod *= temp_count_words;
		}
	}

	for(int i=0; i<count_elem; i++){
		free(word_sent[i]);
	}
	free(word_sent);

	return cur_prod;
}

int cmp(const void* a, const void* b){
	struct Sentence **first_sent = (struct Sentence **) a;
	struct Sentence **second_sent = (struct Sentence **) b;

	int first = count_prod(*first_sent);
	int second = count_prod(*second_sent);

	if (first < second) return 1; 
	if (first > second) return -1; 
	return 0;
}

void sort_sents(struct Text *text){
	qsort(text->sents, text->n, sizeof(struct Sentence *), cmp);
}