#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "structs.h"
void Task_4(Text* text_p){
    int i=0,j,k,flag;
    while(i<text_p->leng_text){ //перебираем предложения
        flag=1,j=0;
        while(flag&&j<text_p->buf_sents[i].leng_str) {//перебираем символы внутри .str_sent
            wchar_t c = text_p->buf_sents[i].str_sent[j];
            if(c=='1'||c=='3'||c=='5'||c=='7'||c=='9'){
                for(k=i;k<text_p->leng_text-1;k++){
                    text_p->buf_sents[k]=text_p->buf_sents[k+1];
                }
                text_p->leng_text-=1;
                flag=0;
            }
            else {
                j++;
            }
        }
        if(flag==1)i++;
    }
}
