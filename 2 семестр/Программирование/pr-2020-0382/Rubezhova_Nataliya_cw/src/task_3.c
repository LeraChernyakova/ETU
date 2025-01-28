#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "structs.h"
#include "task_3.h"
void Task_3(Text* text_p){
    int i,j,k;
    wchar_t numbers[]=L"0123456789";
    for(i=0;i<text_p->leng_text;i++){
        for(j=0;j<text_p->buf_sents[i].leng_str;j++){
            wchar_t c=text_p->buf_sents[i].str_sent[j];
            wchar_t* is_num=wcschr(numbers,c);
            if(is_num!=NULL) {
                if((*(is_num)=='2')||(*(is_num)=='3')){
                    text_p->buf_sents[i].str_sent=(wchar_t*)realloc(text_p->buf_sents[i].str_sent,(text_p->buf_sents[i].leng_str+1)*sizeof(wchar_t));
                    for(k=text_p->buf_sents[i].leng_str;k>j;k--){
                        text_p->buf_sents[i].str_sent[k+1]=text_p->buf_sents[i].str_sent[k];
                    }
                    text_p->buf_sents[i].str_sent[j]='1';
                    if(*(is_num)=='2')
                        text_p->buf_sents[i].str_sent[j+1]='0';
                    else
                        text_p->buf_sents[i].str_sent[j+1]='1';
                }
                if((*(is_num)=='4')||(*(is_num)=='5')||(*(is_num)=='6')||(*(is_num)=='7')) {
                    text_p->buf_sents[i].str_sent = (wchar_t *) realloc(text_p->buf_sents[i].str_sent,
                                                                        (text_p->buf_sents[i].leng_str + 2) *
                                                                        sizeof(wchar_t));
                    for (k = text_p->buf_sents[i].leng_str; k > j; k--) {
                        text_p->buf_sents[i].str_sent[k + 2] = text_p->buf_sents[i].str_sent[k];
                    }
                    text_p->buf_sents[i].str_sent[j] = '1';
                    switch (*(is_num)) {
                        case L'4':
                            text_p->buf_sents[i].str_sent[j + 1] = '0';
                            text_p->buf_sents[i].str_sent[j + 2] = '0';
                            break;
                        case L'5':
                            text_p->buf_sents[i].str_sent[j + 1] = '0';
                            text_p->buf_sents[i].str_sent[j + 2] = '1';
                            break;
                        case L'6':
                            text_p->buf_sents[i].str_sent[j + 1] = '1';
                            text_p->buf_sents[i].str_sent[j + 2] = '0';
                            break;
                        case L'7':
                            text_p->buf_sents[i].str_sent[j + 1] = '1';
                            text_p->buf_sents[i].str_sent[j + 2] = '1';
                            break;
                    }
                }
                if((*(is_num)=='8')||(*(is_num)=='9')){
                    text_p->buf_sents[i].str_sent=(wchar_t*)realloc(text_p->buf_sents[i].str_sent,(text_p->buf_sents[i].leng_str+3)*sizeof(wchar_t));
                    for(k=text_p->buf_sents[i].leng_str;k>j;k--){
                        text_p->buf_sents[i].str_sent[k+3]=text_p->buf_sents[i].str_sent[k];
                    }
                    text_p->buf_sents[i].str_sent[j]='1';
                    text_p->buf_sents[i].str_sent[j+1]='0';
                    text_p->buf_sents[i].str_sent[j+2]='0';
                    if(*(is_num)=='8')
                        text_p->buf_sents[i].str_sent[j+3]='0';
                    else
                        text_p->buf_sents[i].str_sent[j+3]='1';

                }
            }
        }
    }
}

