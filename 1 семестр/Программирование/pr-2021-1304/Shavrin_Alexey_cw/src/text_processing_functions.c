#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include <string.h>
#include "my_struct.h"
#define COUNSONANTS L"BbCcDdFfGgHhJjLlKkMmNnPpQqRrSsTtVvWwXxZzБбВвГгДдЖжЗзЙйКкЛлМмНнПпРрСсТтФфХхЦцЧчШшЩщ"


void freeSentence(struct Sentence sent){
	for (struct Word *word = sent.wwords; word < sent.wwords + sent.count_w; word++){
		free(word -> wchars);	//cleaning memory
	}
	free(sent.wwords);	//cleaning memory
}


void freeText(struct Text *text){
	for (int i = 0; i < text -> count_s; i++){
		freeSentence(text -> sents[i]);	//cleaning memory
	}
	free(text -> sents);	//cleaning memory
	text -> sents = NULL;
	text -> count_s = 0;

}

void removingSentence(struct Text *text, int index){
	freeSentence(text -> sents[index]);	//cleaning memory
	memmove(text -> sents+index, text -> sents+index+1, (text -> count_s-index-1)*sizeof(struct Sentence));	//shift of sentences in the text
	text -> count_s--;	//overwrite count of sentences in the text
}


void removingDuplicateSentences(struct Text *text){
	int count = 0;	//count removing sentences
	int coincidence1, coincidence2;
	struct Word *word1;
	struct Word *word2;
	for (int rs = text -> count_s-1; rs > 0; rs--){
		for (int ls = rs-1; ls >= 0; ls--){
			if (text -> sents[ls].count_w == text -> sents[rs].count_w){
				word1 = text -> sents[ls].wwords;
				word2 = text -> sents[rs].wwords;
				coincidence1 = coincidence2 = 0;
				for (int i = 0; i < text -> sents[ls].count_w; i++){
					coincidence1 = word1[i].sep != word2[i].sep;
					coincidence2 = wcscasecmp(word1[i].wchars, word2[i].wchars);
					if (coincidence1 || coincidence2)
						break;
				}
				if (!coincidence1 && !coincidence2){
					removingSentence(text, rs);
					count++;
					break;
				}
			}	
		}
	}
	wprintf(L"Было удалено %d повторяющихся предложений.\n", count);
}


void sumSec(struct Text *text){
	float sum_sec = 0;
	int num;
	int is_sec;
	for (struct Sentence *sent = text -> sents; sent < text -> sents + text -> count_s; sent++){
		if (sent -> count_w >= 2){
			for (struct Word *word = sent -> wwords; word < sent -> wwords + sent -> count_w - 1; word++){
				wchar_t *pEnd;
				num = wcstol(word -> wchars, &pEnd, 10);
				is_sec = wcscasecmp(L"sec", (word+1) -> wchars);
				if (num && !is_sec){
					sum_sec += num;
				}	
			}
		}
	}
	wprintf(L"Количество секунд встречающихся в тексте равно %f минут.\n", sum_sec/60);
}


void removingSertainSentences(struct Text *text){
	int count = 0;
	int count_counsonants = 0;
	for (int i = text -> count_s -1; i >= 0; i--){
		int last_word = text -> sents[i].count_w-1;
		struct Word word = text -> sents[i].wwords[last_word];
		for (int j = 0; j < word.count_c; j++){
			wchar_t s = word.wchars[j];
			if (wcschr(COUNSONANTS, s))
				count_counsonants++;
			else
				count_counsonants = 0;
			if (count_counsonants == 3){
				removingSentence(text, i);
				count++;
				break;
			}	
		}
	}
	wprintf(L"Было удалено %d предложений\n", count);
}


int sumCode(struct Sentence *sent){
	int s = 0;
	for (int i = 0; i < sent -> wwords[0].count_c; i++){
		s += sent -> wwords[0].wchars[i];
	}
	return s;
}


int funccmp(const void *x1, const void *x2){
	int sc1 = sumCode((struct Sentence*)x1);
	int sc2 = sumCode((struct Sentence*)x2);
	return sc1 - sc2;
}


void replaceSymbol(struct Text *text){
	for (struct Sentence *sent = text -> sents; sent < text -> sents + text -> count_s; sent++){
		for (struct Word *word = sent -> wwords; word < sent -> wwords + sent -> count_w; word++){
			int size = word -> count_c + 1;
			wchar_t *new_word = malloc(size*sizeof(wchar_t));
			int j = 0;
			for (int i = 0; i <= word -> count_c; i++){
				if (word -> wchars[i] != L'%' && word -> wchars[i] != L'#' && word -> wchars[i] != L'@'){
					new_word[j++] = word -> wchars[i];
				}
				else{
					if (word -> wchars[i] == L'%' || word -> wchars[i] == L'#'){
						size += 8;
						new_word = realloc(new_word, size*sizeof(wchar_t));
						if (word -> wchars[i] == L'%'){
							wchar_t prec[] = L"<precent>\0";
							for (int k = 0; prec[k]; k++){
								new_word[j++] = prec[k];
							}
						}
						if (word -> wchars[i] == L'#'){
							wchar_t resh[] = L"<решётка>\0";
							for (int k = 0; resh[k]; k++){
								new_word[j++] = resh[k];
							}
						}
					}
					else{
						size += 3;
						new_word = realloc(new_word, size*sizeof(wchar_t));
						if (word -> wchars[i] == L'@'){
							new_word[j++] = L'(';
							new_word[j++] = L'a';
							new_word[j++] = L't';
							new_word[j++] = L')';
						}
					}
				}
			}
			free(word -> wchars);
			word -> wchars = new_word;
			word -> count_c = j;
		}
	}
}
