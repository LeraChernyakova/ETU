#include <wchar.h>
#include <locale.h>
#include "structs.h"
#include "task_1.h"
void Task_1(Text* text_p){
    int i,j;
    wchar_t trans_up[]=L"ABVGDEËŽZIJKLMNOPRSTUFHCČŠŜʺYʹÈÛÂ";
    wchar_t trans_low[]=L"abvgdeëžzijklmnoprstufhcčšŝʺyʹèûâ";
    wchar_t cyr_up[]=L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    wchar_t cyr_low[]=L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    for(i=0;i<text_p->leng_text;i++){
        for(j=0;j<text_p->buf_sents[i].leng_str;j++){
            wchar_t c=text_p->buf_sents[i].str_sent[j];
            wchar_t* up=wcschr(cyr_up,c);
            if(up!=NULL) {
                text_p->buf_sents[i].str_sent[j]=*(up-cyr_up+trans_up);
            }
            else{
                wchar_t* low = wcschr(cyr_low,c);
                if(low!=NULL){
                    text_p->buf_sents[i].str_sent[j]=*(low-cyr_low+trans_low);
                }
            }

        }
    }
}

