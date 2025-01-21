#include "txtio.h"

Word readWord(){
	int size = MEM_STEP, len = 0;
	wchar_t* wchars = malloc(size*sizeof(wchar_t));
	wchar_t sep, wc = L' ';
	
	while (wc == L' ') wc = fgetwc(stdin);
	while (!wcschr(WORD_SEP, wc) && !wcschr(SENT_SEP, wc)){
		wchars[len++] = wc;
		if (len == size){
			size += MEM_STEP;
			wchars = realloc(wchars, size*sizeof(wchar_t));
		}
		wc = fgetwc(stdin);
	}
	wchars[len] = L'\0';
	sep = wc;
	return (Word){wchars, sep, size, len};
}

Sentence readSentence(){
	int size = MEM_STEP, len = 0;
	Word* words = malloc(size*sizeof(Word));
	Word ww;
	
	do{
		ww = readWord();
		if (len == size){
			size += MEM_STEP;
			words = realloc(words, size*sizeof(Word));
		}
		words[len++] = ww;
	} while (!wcschr(SENT_SEP, ww.sep));
	return (Sentence){words, size, len};
}

Text readText(){
	int size = MEM_STEP, len = 0;
	Sentence* sents = malloc(size*sizeof(Sentence));
	Sentence ws;
	
	do{
		ws = readSentence();
		if (ws.len == 1 && !ws.words[0].len && ws.words[0].sep == L'\n'){
			free(ws.words[0].wchars);
			free(ws.words);
			break;
		}
		if(len == size){
			size += MEM_STEP;
			sents = realloc(sents, size*sizeof(Sentence));
		}
		sents[len++] = ws;
	} while (ws.words[ws.len-1].sep != L'\n');
	if (ws.words[ws.len-1].sep == L'\n')
		ws.words[ws.len-1].sep = L'.';
	return (Text){sents, size, len};
}

void printText(Text text){
	for (Sentence* ws = text.sents; ws < text.sents + text.len; ws++)
		for (Word* ww = ws->words; ww < ws->words + ws->len; ww++){
			fputws(ww->wchars, stdout);
			fputwc(ww->sep, stdout);
			if (ww->sep != L' ') fputwc(L' ', stdout);
		}
	fputwc(L'\n', stdout);
}
