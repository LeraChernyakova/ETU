#include "top_header.h"
#include "primitiv_func.h"
#include "write.h"


void write(Text _text, int flag_n){
    wprintf(L"\nРезультат:\n");
    switch (flag_n) {

        case 1:
            if (_text.volume_gr_anagram == 0){
                wprintf(L"Ненайденно \n\n");
                break;
            }

            for (int i = 1; i <= _text.volume_gr_anagram; i++) {//вывод по групам анаграмм
                wprintf(L"%i.\n",i);

                for (int j = 0;j < _text.size;  j++){//проверка каждого sent на принадлежность к группе анаграмм
                    if (_text.sents[j].group_anagram == i){
                        wprintf(L"\t%ls\n", _text.sents[j].str);
                    }
                }
                wprintf(L"\n");

            }
            break;

        case 2:
            for (int i = 0, j = 1 ; i < _text.size; i++,j++) {
                delt_all_char(&_text.sents[i] , '\n');
                wprintf(L"%i.%ls (%i)\n",j, _text.sents[i].str,_text.sents[i].vol_upper);
                if (_text.sents[i].vol_upper == _text.sents[i+1].vol_upper){j-=1;}
            }
            wprintf(L"\n");
            break;

        case 3:
            for (int i = 0; i < _text.size; i++) {
                wprintf(L"%ls", _text.sents[i].str);
            }
            wprintf(L"\n\n");
            break;

        case 4:
            for (int i = 0; i < _text.size; i++) {
                wprintf(L"%ls", _text.sents[i].str);
            }
            wprintf(L"\n\n");
            break;
	    
       case 6:
            for (int i = 0; i < _text.size; i++) {
                wprintf(L"%ls", _text.sents[i].str);
            }
            wprintf(L"\n\n");
            break;	

    }
    wprintf(L"Чтобы продолжить нажмите Enter:\n");
    while ((getwchar ()) != '\n');
}

