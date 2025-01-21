#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "my_struct.h"
#include "input_output_text_functions.h"
#include "text_processing_functions.h"


int main(){
	setlocale(LC_ALL, "");
	struct Text *text = malloc(sizeof(struct Text));
	struct Text *t;
	wprintf(L"Введите текст:\n");
	t = readText();
	if (t == NULL){
		wprintf(L"Возникла ошибка выделения памяти. Введенный вами текст слишком большой.\n");
	}
	else{
		*text = *t;
		removingDuplicateSentences(text);
		printText(text);
		userChoice(text);
	}
	return 0;
}

