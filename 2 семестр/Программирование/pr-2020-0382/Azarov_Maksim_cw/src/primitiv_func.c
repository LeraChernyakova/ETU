#include "top_header.h"
#include "primitiv_func.h"



void* mem_alloc(int len, int size){ // длинаа , размер типа

    void* p;

    p = malloc(len*size);

    if (p == NULL){
        fprintf(stderr,"Ошибка выделения памяти ");
        exit(1);
    }

    return p;
}


void delt_all_char( Sentence* sent,wchar_t  ch ){
    int i;
    for(i = 0; i < sent->len; i++){
        if (sent->str[i] == ch){
            delt_char(i,sent->str);
            i --;
            sent->len;
        }
    }

}


void delt_char(int num , wchar_t* str ){

    int i;

    for (i = num; str[i]!='\0';i++){
        str[i] = str[i+1];

    }


}
