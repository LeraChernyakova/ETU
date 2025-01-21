#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_struct.h"
#include "text_processing_functions.h"
#define MEM_STEP 5
#define BUF_CHOICE 5
#define WORDS_SEPARATORS L" ,"
#define SENTS_SEPARATORS L".\n"


struct Word *readWord(){
	int size = MEM_STEP;	//buffer size
	int count_c = 0;	//word length(iteration variable)
	wchar_t *temp = malloc(size*sizeof(wchar_t));	//buffer
	wchar_t sep = L' ';	//words separator
	wchar_t wchar = L' ';	//input char
	if (temp != NULL){	//checking memory allocation
		wchar_t *word = temp;
		while (wchar == L' ')	//skipping space
			wchar = fgetwc(stdin);
		while (!wcschr(WORDS_SEPARATORS, wchar) && !wcschr(SENTS_SEPARATORS, wchar)){
			word[count_c++] = wchar;
			if (count_c == size){	//checking for buffer overflow
				size += MEM_STEP;	//increase buffer
				temp = realloc(word, size*sizeof(wchar_t));
				if (temp != NULL)	//checking memory allocation
					word = temp;
				else{
					free(word);	//cleaning memory
					return NULL;
				}
			}
			wchar = fgetwc(stdin);
		}
		word[count_c] = L'\0';
		sep = wchar;
		return &(struct Word){word, sep, count_c};	//casting to type struct Word
	}
	free(temp);
	return NULL;
}	


struct Sentence *readSentence(){
	int size = MEM_STEP;	//buffer size
	struct Word *temp = malloc(size*sizeof(struct Word));	//buffer
	if (temp != NULL){	//checking memory allocation
		struct Word *sent = temp;
		int count_w = 0;	//count words(iteration variable)
		struct Word *ww = malloc(sizeof(struct Word));	//input wide word
		struct Word *cn;	//variable for check NULL
		do{	
			cn = readWord();
			if (cn == NULL){	//checking memory allocation
				freeSentence((struct Sentence){sent, count_w});	//cleaning memory
				return NULL;
			}
			*ww = *cn;
			sent[count_w++] = *ww;
			if (count_w == size){
				size += MEM_STEP;
				temp = realloc(sent, size*sizeof(struct Word));
				if (temp != NULL)	//checking memory allocation
					sent = temp;
				else{
					freeSentence((struct Sentence){sent, count_w});	//cleaning memory
					return NULL;
				}
			}
		}while (!wcschr(SENTS_SEPARATORS, ww->sep));
		free(ww);	//cleaning memory
		return &(struct Sentence){sent, count_w};	//casting to type struct Sentence
	}
	return NULL;
}


struct Text *readText(){
	int size = MEM_STEP;	//buffer size
	struct Sentence *temp = malloc(size*sizeof(struct Sentence));	//buffer
	if (temp != NULL){	//checking memory allocation
		struct Sentence *txt = temp;
		int count_s = 0;	//count sentences(iteration variable)
		struct Sentence *sent = malloc(sizeof(struct Sentence));	//input sentence
		struct Sentence *cn;	//variable for check NULL
		do{
			cn = readSentence();
			if (cn == NULL){	//checking memory allocation
				freeText(&(struct Text){txt, count_s});	//cleaning memory
				return NULL;
			}
			*sent = *cn;
			if (sent->count_w == 1 && !sent->wwords[0].count_c && sent->wwords[0].sep == L'\n'){	//check end text
				free(sent -> wwords[0].wchars);	//cleaning memory
				free(sent -> wwords);	//cleaning memory
				break;
			}
			txt[count_s++] = *sent;
			if (count_s == size){	//checking for buffer overflow
				size += MEM_STEP;	//increase buffer
				temp = realloc(txt, size*sizeof(struct Sentence));	//buffer
				if (temp != NULL){	//checking memory allocation
					txt = temp;
				}
				else{
					freeText(&(struct Text){txt, count_s});	//cleaning memory
					return NULL;
				}
			}
			
		}while (sent->wwords[sent->count_w - 1].sep != L'\n');
		if ((sent->wwords[sent->count_w - 1].sep) == L'\n')
			(sent->wwords[sent->count_w - 1].sep) = L'.';	//adding a dot to an unfinished sentence
		free(sent);	//cleaning memory
		return &(struct Text){txt, count_s};
	}
	return NULL;
}


void printText(struct Text *text){
	for (struct Sentence *sent = text -> sents; sent < text -> sents + text -> count_s; sent++){
		for (struct Word *word = sent -> wwords; word < sent -> wwords + sent -> count_w; word++){
			fputws(word -> wchars, stdout);
			fputwc(word -> sep, stdout);
			if (word -> sep != L' ')
				fputwc(L' ', stdout);
		}
	}
	fputwc(L'\n', stdout);
}


void userChoice(struct Text *text){
	wchar_t choice[BUF_CHOICE] = L"";
	while (choice[0] != L'5'){
		wprintf(L"Выберите, что необходимо сделать с текстом:\n");
		wprintf(L"1 - Посчитать и вывести в минутах количество секунд встречающихся в тексте.\n");
		wprintf(L"2 - Отсортировать предложения по увеличению суммы кодов символов первого слова в предложении.\n");
		wprintf(L"3 - Заменить все символы ‘%’, ‘#’, ‘@’ на “<percent>”, “<решетка>”, “(at)” соответственно.\n");
		wprintf(L"4 - Удалить все предложения которые заканчиваются на слово с тремя согласными подряд.\n");
		wprintf(L"5 - Закончить обработку и завершить программу.\n");
		fgetws(choice, BUF_CHOICE, stdin);
		switch (choice[0]){
			case L'1':
				sumSec(text);
				break;
			case L'2':
				wprintf(L"Результат сортировки:\n");
				qsort(text -> sents, text -> count_s, sizeof(struct Sentence), funccmp);
				printText(text);
				break;
			case L'3':
				wprintf(L"Результат замены:\n");
				replaceSymbol(text);
				printText(text);
				break;
			case L'4':
				removingSertainSentences(text);
				printText(text);
				break;
			case L'5':
				wprintf(L"Обработка завершена. Программа окончена.\n");
				break;
			default:
				wprintf(L"Вы ввели некорректный номер, выберите число от 1 до 5\n");
		}
	}
}

