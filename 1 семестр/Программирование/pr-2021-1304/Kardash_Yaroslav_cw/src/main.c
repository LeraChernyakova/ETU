#include "define.h"
#include "inp_out_free.h"
#include "processing.h"
int main(){
	setlocale(LC_ALL, "");
	wprintf(L"Введите текст в одну строку. Предложения в тексте разделены точкой, слова в предложении пробелом или запятой. Конец ввода - двойное нажатие enter.\n");
	struct Text text = get_Text();
	text=If_Del(text);
	Print_Text(text);
	wprintf(L"\n");
	menu(text);
	Free_Text(text);
	return 0;
}
