#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEM_STEP 100
#define CRASH_MEMORY_MSG L"Ошибка выделения памяти"

#include <wchar.h>
#include <locale.h>

#include "textio.h"

int check_entry(struct Sentence *sentence){

	for(int i=0; i<wcslen(sentence->str); i++){
		wchar_t symbol = sentence->str[i];
		int found_symbol = 0;
		if(symbol == L'#' || symbol == L'№'){
			found_symbol = 1;
			for(int j=0; j<wcslen(sentence->str); j++){
				wchar_t num = sentence->str[j];
				if (num < '0' || num > '9'){
					continue;
				} else {
					return 0;
				}
			}
			if(found_symbol == 0){
				return 0;
			} else {
				return 1;
			}
		}
	}
}

void remove_symbols(struct Text	*text){
	int i = 0;

	while(i < text->n){
		if (check_entry(text->sents[i]) == 1){
			free(text->sents[i]);
			memmove(&text->sents[i], &text->sents[i+1], (text->n-i+1)*sizeof(struct Sentence));
			text->n -= 1;
		} else {
			i++;
		}
	}
}