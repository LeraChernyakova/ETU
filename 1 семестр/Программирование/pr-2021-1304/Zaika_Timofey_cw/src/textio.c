#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEM_STEP 100
#define CRASH_MEMORY_MSG L"Ошибка выделения памяти"

#include <wchar.h> 
#include <locale.h>

struct Sentence{
	wchar_t *str;
	int size;
};

struct Text{
	struct Sentence **sents;
	int n;
	int size;
};

struct Sentence* readSentence();

struct Text readText(){ 
	int size = MEM_STEP;
	struct Sentence** text = malloc(size*sizeof(struct Sentence*));
	if(!text){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
	int n = 0;
	struct Sentence* temp;
	int nlcount = 0;
	do{
		temp = readSentence();
		if(temp->str[0] == '\n'){
			nlcount++;
		} else {
			nlcount = 0;
			text[n] = temp;
			n++;
		}
	} while (nlcount<2);
	struct Text txt;
	txt.size = size;
	txt.sents = text;
	txt.n = n;
	return txt;
}

struct Sentence* readSentence(){
	int size = MEM_STEP;
	wchar_t *buf = malloc(size*sizeof(wchar_t));
	if(!buf){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
	int n = 0;
	wchar_t temp;
	do{
		if (n >= size-2){
			wchar_t *t = realloc(buf, size+MEM_STEP);
			if(!t){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
			size += MEM_STEP;
			buf = t;
		}
		temp = getwchar();
		buf[n] = temp;
		n++;
	} while (temp!='\n' && temp!='.' && temp!='!');
	buf[n] = '\0';
	struct Sentence *sentence = malloc(sizeof(struct Sentence));
	if(!sentence){wprintf(L"%ls\n", CRASH_MEMORY_MSG);}
	sentence -> str = buf;
	sentence -> size = size;
	return sentence;
}

void changed_text(struct Text* text){
	int i = 0;
	int j = i + 1;
	
	while(i < text->n-1){
		while(j < text->n){
			if (wcscasecmp(text->sents[i]->str, text->sents[j]->str) == 0){
				free(text->sents[j]);
				memmove(&text->sents[j], &text->sents[j+1], (text->n-j+1)*sizeof(struct Sentence));
				text->n -= 1;
			} else {
				j++;
			}
		}
		i++;
		j = i + 1;
	}
}

void print_text(struct Text *text){
	for (int i=0; i<text->n; i++){
		wprintf(L"%ls", text->sents[i]->str);
	}
	wprintf(L"%ls\n", L"");
}

void free_text(struct Text *text){
	int text_len = text->n;
	for(int i=0; i<text_len; i++){
		free(text->sents[i]);
	}
}