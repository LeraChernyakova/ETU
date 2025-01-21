#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEM_STEP 100
#define CRASH_MEMORY_MSG L"Ошибка выделения памяти"

#include <wchar.h>
#include <locale.h>

#include "textio.h"

void single_word(struct Text *text){
	wchar_t sep[10] = L" ,!?;\n";
	wchar_t **word_text = malloc(text->n*MEM_STEP*sizeof(wchar_t*));
	if(!word_text){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
	int count_elem = 0;

	for(int i=0; i<text->n; i++){
		wchar_t *cur_sent = text->sents[i]->str;
		wchar_t temp_sent[wcslen(cur_sent)];
		wcscpy(temp_sent, cur_sent);

		wchar_t *istr;
		wchar_t *pwc;
		istr = wcstok(temp_sent, sep, &pwc);
		while(istr != NULL){
			wchar_t *temp = malloc(sizeof(wchar_t*));
			if(!temp){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
			wcscpy(temp, istr);
			word_text[count_elem] = temp;
			count_elem++;
			istr = wcstok(NULL, sep, &pwc);
		}
	}

	for(int j=0; j<count_elem; j++){
		int flag = 0;
		wchar_t *cmp_item = word_text[j];
		for(int k=0; k<count_elem; k++){
			if (j == k){
				continue;
			}
			if(wcscmp(cmp_item, word_text[k]) == 0){
				flag = 0;
				break;
			} else {
				flag = 1;
			}
		}
		if(flag == 1){
			wprintf(L"%ls\n", cmp_item);
		}
	}

	for(int i=0; i<count_elem; i++){
		free(word_text[i]);
	}
	free(word_text);
}