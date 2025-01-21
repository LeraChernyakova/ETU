#include "define.h"
#include "inp_out_free.h"
#include "processing.h"
void menu(struct Text text) {

	int menu_input = 0;
	do{
		wprintf(L"Выберите одно из предложенных действий:\n");
		wprintf(L"1: “Раскрасить” каждое слово в зависимости от остатка от деления его длины на 4. Если остаток равен 0 - красный цвет, 1 - синий, 2 - зеленый, 3 - желтый.\n");
		wprintf(L"2: Распечатать каждое слово которое начинается и заканчивается на заглавную букву и номера предложений в которых оно встречается .\n");
		wprintf(L"3: Отсортировать предложения по длине последнего слова в предложении.\n");
		wprintf(L"4: Удалить все числа из предложений. Число - набор подряд идущих цифр, перед и после которого стоят пробелы.\n");
		wprintf(L"5: Выход\n");
		wscanf(L"%d", &menu_input);
		switch (menu_input) {
			case 1:Colour_Words(text);
				break;
				
			case 2: Upp_Words(text);
				break;
			case 3: qsort(text.t,text.len,sizeof(struct Sentence*),cmp);
		Print_Text(text);
				break;
			case 4: text= Del_Digit(text);
				Print_Text(text);
				break;
			case 5: wprintf(L"Программа завершена по требованию пользователя\n");
				break;
	}
	}while(menu_input!=5);

}


struct Sentence* get_Sent(){
	int size = STAND_SENT;
	wchar_t *buf = malloc(size*sizeof(wchar_t));
	if (buf){
	    wchar_t temp;
	    int i=0;
	    do{
		    if(i>=size-2){// выделяем доп память
				wchar_t *t = realloc(buf,size+STAND_SENT);
				if (t){
				    size+=STAND_SENT;
				    buf = t;}
                else{
                    wprintf(L"Ошибка при довыделении памяти, пожалуйста, завершите ввод а затем завершите программу");
                    break;
                    }

		        }

	   	        temp=getwchar();
		        buf[i]=temp;
		        i++;
	        }while(temp!='\n' && temp!='.');
	    buf[i]='\0';
	    struct Sentence *b = malloc(sizeof(struct Sentence));
	    if(b){
            struct Sentence * sent=b;
            sent->s = buf;
            sent->size = size;
            return sent;
	    }
	    else{
            struct Sentence* er_sent;
            wprintf(L"Ошибка при выделении памяти, пожалуйста, закончите ввод и завершите программу");
            return er_sent;
            }
	}
    else{
        struct Sentence* er_sent;
        wprintf(L"Ошибка при выделении памяти, пожалуйста, закончите ввод и завершите программу");
        return er_sent;
    }
}

struct Text get_Text(){
	int size=STAND_TXT;
	struct Sentence** text = malloc(size*sizeof(struct Sentence*));
	if (text){
	    	int len=0;
	    	struct Sentence* temp;
	    	int n_leack=0;
	    	do{
		    	temp = get_Sent();
		    	if(temp->s[0]=='\n'){
			    n_leack++;
			    free(temp->s);
			    free(temp);
		    	}else{
			    	n_leack=0;
 			    	text[len]=temp;
               		    len++;

			    }
	    	}while(n_leack<2);
		
	    struct Text all_text;
	    all_text.size = size;
	    all_text.t = text;
	    all_text.len =len;
	    
	    return all_text;
	}
	else{
	struct Text er_text;
	er_text.len=0;
	wprintf(L"Ошибка при выделении памяти, пожалуйста, завершите программу.");
	return er_text;}
}
void Print_Text(struct Text text){
	for(int i=0;i<text.len;i++){
		wprintf(L"%ls",text.t[i]->s);
		}
	wprintf(L"\n");

}



void Free_Text(struct Text text){
	for(int i=0;i<text.len;i++){
		free(text.t[i]->s);
	}
	free(*text.t);
	free(text.t);
}
