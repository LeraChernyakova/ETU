#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "structs.h"
#include "task_2.h"
int compare(const void* a,const void* b){
    int temp_a=*(int*)a;
    int temp_b=*(int*)b;
    if(temp_a>temp_b)
        return -1;
    if(temp_a==temp_b)
        return 0;
    if(temp_a<temp_b)
        return 1;
}
void Task_2(Text* text_p){
    int i,j;
    for(i=0;i<text_p->leng_text;i++) {//перебираем предложения
        int* buf_ints=(int*)calloc((text_p->buf_sents[i].leng_str),sizeof(int));
        int leng_buf_ints=0;
        for (j = 0; j < text_p->buf_sents[i].leng_str; j++) {//перебираем символы внутри предложения
            wchar_t c = text_p->buf_sents[i].str_sent[j];
            wchar_t symbols[]=L"!\"#$%&'()*+-/:;<=>?@[\\]^_`{|}~";
            wchar_t* srch=wcschr(symbols,c);
            if(srch!=NULL){
                int code=*(srch);
                buf_ints[leng_buf_ints++]=code;
            }
        }
        if(leng_buf_ints!=0)text_p->buf_sents[i].buf_codes_symb=(int*)malloc(leng_buf_ints*sizeof(int));
        for(j=0;j<leng_buf_ints;j++){
            text_p->buf_sents[i].buf_codes_symb[j]=buf_ints[j];
        }
        text_p->buf_sents[i].leng_buf_codes_symb=leng_buf_ints;
        free(buf_ints);
    }
    wprintf(L"Спецсимволы в порядке уменьшения кодов: ");
    for(i=0;i<text_p->leng_text;i++){
        if(text_p->buf_sents[i].leng_buf_codes_symb==0)wprintf(L"У предложения спецсимволы отсуствуют. ");
        else {
            qsort(text_p->buf_sents[i].buf_codes_symb, text_p->buf_sents[i].leng_buf_codes_symb, sizeof(int), compare);
            for (j = 0; j < text_p->buf_sents[i].leng_buf_codes_symb; j++) {
                wprintf(L"%lc", text_p->buf_sents[i].buf_codes_symb[j]);
            }
            wprintf(L" ");
        }
    }
}

