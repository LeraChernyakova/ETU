#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#include "structs.h"
#include "input_f.h"
#include "task_1.h"
#include "task_2.h"
#include "task_3.h"
#include "task_4.h"

int main() {
    setlocale(LC_ALL,"");
    Text inp;
    wchar_t c=' ';
    wprintf(L"Введите текст:\nПримечание: между словами может быть пробел или запятая, предложения отделены точкой\n");
    c=getwchar();
    get_Text(c,&inp);
    int i;
    get_str_sent(&inp);
    for(i=0;i<inp.leng_text;i++){
        check_repeat(&(inp),&(inp.buf_sents[i]));
    }
    int com;
    wprintf(L"Введите команду:\n1 - сделать транслитерацию всех кириллических символов в тексте\n");
    wprintf(L"2 - вывести для каждого предложения все специальные символы в порядке уменьшения их кода\n");
    wprintf(L"3 - заменить все цифры в тексте их двоичным кодом\n");
    wprintf(L"4 - удалить все предложения, в которых есть нечетные цифры\n");
    wprintf(L"5 - вывести текст\n");
    wprintf(L"0 - завершить программу\n");
    wscanf(L"%d",&com);
    while(com!=0){
        switch(com) {
            case 1:
                Task_1(&inp);
                break;
            case 2:
                Task_2(&inp);
                break;
            case 3:
                Task_3(&inp);
                break;
            case 4:
                Task_4(&inp);
                break;
            case 5:
                for (i = 0; i < inp.leng_text; i++) {
                    wprintf(L"%ls", inp.buf_sents[i].str_sent);
                }
                wprintf(L"\n");
                break;
            default:
                if (com != 0)wprintf(L"Неверная команда\n");
        }
        if(com!=0){
           wprintf(L"Введите следующую команду:\n");
           wscanf(L"%d",&com);
        }
    }
    return 0;
}
