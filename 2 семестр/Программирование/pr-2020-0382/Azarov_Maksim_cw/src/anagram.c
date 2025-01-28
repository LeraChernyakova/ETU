#include "top_header.h"

#include "primitiv_func.h"
#include "anagram.h"

Text find_anagram(Text _text){

    int i,j;

    //обнуляем anagrm
    for(i = 0 ; i < _text.size ; i++){
        _text.sents[i].group_anagram = 0;
    }

    int numb = 0 ; //сквозная нумерация групп анаграмм
    int last_i = -1;//запоминает предыдушее значение i

    for(i = 0; i < _text.size ; i++){
        for(j = i+1; j < _text.size ; j++){
            if (is_anagram(_text.sents[i],_text.sents[j])&&(_text.sents[j].group_anagram == 0)){
                if (i != last_i){numb+=1;}
                _text.sents[i].group_anagram = numb;
                _text.sents[j].group_anagram = numb;
                last_i = i;
            }
        }
    }

    _text.volume_gr_anagram = numb;

    return _text;

}



int is_anagram(Sentence s1 , Sentence s2) {
    int j;
    wchar_t* p1;// промежуточные укозатели
    wchar_t* p2;

    //делаем копии s1 s2 , чтобы можно было их изменять
    p1 = mem_alloc(s1.avlb_len+1,sizeof(wchar_t)); //+1 на всякий случай
    p2 = mem_alloc(s2.avlb_len+1,sizeof(wchar_t));

    wcscpy(p1,s1.str);
    wcscpy(p2,s2.str);

    s1.str = p1;
    s2.str = p2;

    //удаляем лишнее
    for (j = 0; j < s1.len; j++) {
        if (!iswalpha(s1.str[j]) && !iswdigit(s1.str[j])) {
            delt_char(j, s1.str);
            j = j - 1;
            s1.len--;
        }
    }

    for (j = 0; j < s2.len; j++) {
        if (!iswalpha(s2.str[j]) && !iswdigit(s2.str[j])) {
            delt_char(j, s2.str);
            j = j - 1;
            s2.len--;
        }
    }

    if(s1.len!=s2.len){
        free(p1);
        free(p2);
        return 0;
    }
    else{
        qsort(s1.str,s1.len,sizeof(wchar_t),cmp1);
        qsort(s2.str,s2.len,sizeof(wchar_t),cmp1);

        for (int i = 0 ;i < s1.len;i++){
            if (s1.str[i]!=s2.str[i]){
                free(p1);
                free(p2);
                return 0;
            }
        }
        free(p1);
        free(p2);
        return 1;
    }

}


int cmp1(const void* a ,const void* b){
    wchar_t* ch1 = (wchar_t*)a;
    wchar_t* ch2 = (wchar_t*)b;

    if (*ch1>*ch2) {
        return 1;
    }else{
        return 0;}
}



