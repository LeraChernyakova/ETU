#include "inputoutput.h" 
#include "processing.h"


int main()
{	
	setlocale(LC_ALL,"");
	wprintf(L"Введите текст:\n");
	struct Text text=readText();
	wchar_t k,c;
	int flag,i;
	remove_repetes(&text);
	wprintf(L"Выберите желаемое действие:\n");
	wprintf(L"Введите 1, если хотите для каждого предложения вывести “Палиндромы на месте!” если все слова являются палиндромами, “Кто-то потерял все палиндромы.” если ни одного слово не 	является палиндромом, в остальных случаях “Чего-то не хватает.”\n");
	wprintf(L"Введите 2, если хотите заменить все специальные символы (включая .,;) в тексте на подстроку “>special symbol<”.\n");
	wprintf(L"Введите 3, если хотите отсортировать предложения по уменьшению количества латинских букв.\n");
	wprintf(L"Введите 4, если хотите удалить все предложения в которых в одном слове встречаются латинские и кириллические буквы.\n");
	wprintf(L"Введите 5, если хотите вывести текст.\n");
	wprintf(L"Введите 6, если хотите завершить работу программы.\n");
	k=getwchar();
	flag=0;
	while (flag!=1){
		switch(k){
			case L'1':
				palindroms(&text);
				break;
			case L'2':
				replace(&text);
				break;
			case L'3':
				qsort(text.sents, text.size, sizeof(struct Sentence**), funcmp);
				break;
			case L'4':
				delete_lat_and_kir(&text);
				break;
			case L'5':
				output(&text);
				break;
			case L'6':
				flag=1;
				break;
			case L'\n':
				break;
			default:
				wprintf(L"Введите число от 1 до 6\n");
				break;
		}
		k=getwchar();
		//c=getwchar();
	}
	for(i=0;i<text.size;i++){
		free(text.sents[i]->str);
	}
	for(i=0;i<text.size;i++){
		free(text.sents[i]);
	}
}
