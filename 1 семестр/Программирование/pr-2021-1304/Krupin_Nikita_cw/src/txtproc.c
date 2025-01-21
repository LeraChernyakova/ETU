#include "txtproc.h"

int removeDuplicate(Text* text){
	int cond1, cond2, count = 0;
	Word *w1, *w2;
	
	for (int ir = text->len-1; ir > 0; ir--)
		for (int il = ir-1; il >= 0; il--){
			if (text->sents[il].len != text->sents[ir].len)
				continue;
			w1 = text->sents[il].words;
			w2 = text->sents[ir].words;
			cond1 = cond2 = 0;
			for (int i = 0; i < text->sents[il].len; i++){
				cond1 = wcscasecmp(w1[i].wchars, w2[i].wchars);
				cond2 = w1[i].sep != w2[i].sep;
				if (cond1 || cond2) break;
			}
			if (!cond1 && !cond2){
				removeSentence(ir, text);
				count++;
				break;
			}
		}
	return count;
}

void swapWordEnds(Text text){
	wchar_t* wpointer;
	
	for (Sentence* ws = text.sents; ws < text.sents+text.len; ws++)
		for (Word* ww = ws->words; ww < ws->words+ws->len; ww++){
			wpointer = ww->wchars + ww->len;
			if (!wcscasecmp(wpointer-3, L"тся")){
				if (ww->size < ww->len+2){
					ww->size++;
					ww->wchars = realloc(ww->wchars, ww->size*sizeof(wchar_t));
					wpointer = ww->wchars + ww->len;
				}
				memmove(wpointer-1, wpointer-2, 3*sizeof(wchar_t));
				if (iswupper(wpointer[-1]))
					wpointer[-2] = L'Ь';
				else wpointer[-2] = L'ь';
				ww->len++;
			} else if (!wcscasecmp(wpointer-4, L"ться")){
				memmove(wpointer-3, wpointer-2, 3*sizeof(wchar_t));
				ww->len--;
			}
		}
}

void findWord(int is, int iw, Text text){
	int print, count = 0;
	wchar_t* fw;
	
	if (is<text.len && iw<text.sents[is].len){
		fw = text.sents[is].words[iw].wchars;
		for (Sentence* ws = text.sents; ws < text.sents+text.len; ws++){
			print = 0;
			for (Word* ww = ws->words; ww < ws->words+ws->len; ww++)
				if (!wcscasecmp(ww->wchars, fw)){
					print = 1;
					break;
				}
			if (!print) continue;
			for (Word* ww = ws->words; ww < ws->words+ws->len; ww++){
				if (!wcscasecmp(ww->wchars, fw)){
					count++;
					fputws(L"\033[0;32m", stdout);
				}
				fputws(ww->wchars, stdout);
				fputws(L"\033[0m", stdout);
				fputwc(ww->sep, stdout);
				if (ww->sep != L' ') fputwc(L' ', stdout);
			}
			fputwc(L'\n', stdout);
		}
		fputws(L"\033[0;32mНайдено: ", stdout);
		wprintf(L"%d\033[0m\n", count);
	} else fputws(L"\033[0;31mНечего искать. :(\033[0m\n", stdout);
}

int sentCmp (const void* arg1, const void* arg2){
	Sentence* ws1 = (Sentence*)arg1;
	Sentence* ws2 = (Sentence*)arg2;
	
	return ws1->len - ws2->len;
}

int removeSents(Text* text){
	int count = 0;
	
	for (int i = text->len-1; i >= 0; i--)
		if (text->sents[i].len > 10){
			removeSentence(i, text);
			count++;
		}
	return count;
}

void removeSentence(int i, Text* text){
	freeSentence(text->sents[i]);
	memmove(text->sents+i, text->sents+i+1, (text->len-i-1)*sizeof(Sentence));
	text->len--;
}

void freeSentence(Sentence ws){
	for (Word* ww = ws.words; ww < ws.words + ws.len; ww++)
		free(ww->wchars);
	free(ws.words);
}

void freeText(Text* text){
	for (int i = 0; i < text->len; i++)
		freeSentence(text->sents[i]);
	free(text->sents);
	text->sents = NULL;
	text->size = 0;
	text->len = 0;
}
