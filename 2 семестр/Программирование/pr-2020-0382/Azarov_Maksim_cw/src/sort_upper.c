#include "top_header.h"
#include "primitiv_func.h"
#include "sort_upper.h"

Text sort_text_upper(Text _text){
    Text new_text;
    int i,j;

    //полное копирование текста
    new_text.sents = mem_alloc(_text.avlb_size,sizeof(Sentence));//незабудь очисить

    for (i = 0 ; i < _text.size; i++){
        new_text.sents[i].avlb_len = _text.sents[i].avlb_len;
        new_text.sents[i].str = mem_alloc(_text.sents[i].avlb_len,sizeof(wchar_t));//незабудь очисить
        new_text.sents[i].len = _text.sents[i].len;
        wcscpy(new_text.sents[i].str,_text.sents[i].str);
    }
    new_text.size = _text.size;
    new_text.avlb_size =_text.avlb_size;

    //обнуление vol_upper
    for(i = 0; i <new_text.size ; i++){
        new_text.sents[i].vol_upper = 0;
    }

    //подсчет количества заглавных букв в new_text
    for (i = 0 ; i < new_text.size ; i++){
        for (j = 0; j < new_text.sents[i].len; j++){
            if (iswupper(new_text.sents[i].str[j])){
                new_text.sents[i].vol_upper++;
            }
        }
    }


    qsort(new_text.sents, new_text.size, sizeof(Sentence), sort_upper);


    return new_text;
}



int sort_upper(const void* a ,const void* b){
    Sentence sent1 = *(Sentence*) a;
    Sentence sent2 = *(Sentence*) b;
    


    return    sent2.vol_upper - sent1.vol_upper    ;
}
