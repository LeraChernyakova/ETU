//
//
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "text_processing.h"
struct Sentence{
    wchar_t *words;
    int size;
    int len;

};
struct Text{
    struct Sentence **sentences;
    int size;
    int n;
};

struct Mask{
    wchar_t *masks;
};



struct Text del_rep(struct Text text){


    wchar_t *check_words;//строчки для сравнения
    wchar_t *word_now;
    struct Text new_text=text;
    int len_of_txt=new_text.n;


    for(int i=0;i<len_of_txt;i++){
        check_words=new_text.sentences[i]->words;//check_words пробегается по всем предложениям
        int len_w_check=new_text.sentences[i]->len;
        for(int j=i+1;j<len_of_txt;j++){
            word_now=new_text.sentences[j]->words;//текущее предложение
            int len_w_now=new_text.sentences[j]->len;
            int len=new_text.sentences[j]->len;
            int check_symb=0;
            ////посимвольное сравнение
            if(len_w_check==len_w_now) {
                for (int k = 0; k < len; k++) {
                    if (towupper(word_now[k]) == towupper(check_words[k])) {

                        check_symb = 1;
                    } else {
                        check_symb = 0;
                        break;
                    }
                }
            }
            ////
            if(check_symb){//если предложения совпали сдвигаем массив так, чтобы удалить повторяющееся предложение

                //wprintf(L"%ls %ls\n",word_now,check_words);
                free(new_text.sentences[len_of_txt]);
                memmove(&new_text.sentences[j],&new_text.sentences[j+1],(len_of_txt-j)*sizeof(struct Sentence*));
                len_of_txt--;
                j--;

            }


        }

    }

    new_text.n=len_of_txt;

    return new_text;
}


struct Mask* task1(struct Text text){
    int len_of_txt=text.n;
    struct Mask *mask= malloc(sizeof (struct Mask)*len_of_txt);

    for(int i=0;i<len_of_txt;i++) {
        int max=0,min;
        int full_len = text.sentences[i]->len;
        wchar_t str[full_len + 2];
        wcscpy(str, text.sentences[i]->words);

        wchar_t *tr;
        wchar_t *token = wcstok(str, L" ,.", &tr);

        wchar_t *list_of_words[full_len];
        int kol = 0;
        //массив из слов
        while (token != NULL) {
            list_of_words[kol++] = token;

            token = wcstok(NULL, L" ,.", &tr);
        }


        min= wcslen(list_of_words[0]);

        for(int h=0;h<kol;h++ ){

            if(max < wcslen(list_of_words[h])){
                max= wcslen(list_of_words[h]);

            }
            if(min>wcslen(list_of_words[h])){
                min=wcslen(list_of_words[h]);
            }

        }


        wchar_t *mask_first = malloc(sizeof (wchar_t)*(max+2));//максимальной длины

        if(kol>1){
            int z;
            int min_len;
            if(wcslen(list_of_words[0])<wcslen(list_of_words[1])){
                min_len=wcslen(list_of_words[0]);
            }else{
                min_len=wcslen(list_of_words[1]);
            }

            for(z=0;z< min_len;z++){
                if(list_of_words[0][z]==list_of_words[1][z]){
                    mask_first[z]=list_of_words[0][z];
                }else{
                    mask_first[z]='?';
                }
            }
            if(wcslen(list_of_words[0])!= wcslen(list_of_words[1])){
                mask_first[z]='*';
            }
        }else{
            wcscpy(mask_first,list_of_words[0]);
            mask[i].masks=mask_first;
            continue;
        }



        for(int q=1;q<kol-1;q++){

            wchar_t* word_now=list_of_words[q];
            wchar_t* word_next=list_of_words[q+1];
            int index;

            for(index=0;index< min;index++){

                if((word_now[index]==word_next[index]) && (word_next[index]==mask_first[index]) && (word_now[index]==mask_first[index])){
                    //если совпали не изменять


                }else{

                    mask_first[index]='?';
                }
            }

            if(wcslen(word_now)!= wcslen(word_next)){
                if(mask_first[index-1]!='*'){
                    mask_first[index]=L'*';
                    mask_first[index+1]=L'\0';
                }else{
                    mask_first[index]= L'\0';
                }

            }


        }
        mask[i].masks=mask_first;

    }



    return mask;
}



struct Text task2(struct Text text){


    int len_of_txt=text.n;

    for(int i=0;i<len_of_txt;i++){
        int full_len=text.sentences[i]->len;
        wchar_t str[full_len+2];
        wcscpy(str,text.sentences[i]->words);


        wchar_t *tr;
        wchar_t *token=wcstok(str,L" ,.",&tr);


        wchar_t *list_of_words[full_len];
        int kol=0;
        do {
            list_of_words[kol++]=token;
            token = wcstok(NULL, L" ,.", &tr);
        } while (token!=NULL);



        int kol_up=0;

        for(int q=0;q<kol;q++){
            if(list_of_words[q][0]== towupper(list_of_words[q][0])){
                kol_up++;
            }

        }
        if(kol_up!=kol){//если не все слова с заглавной буквы

            free(text.sentences[len_of_txt]);
            memmove(&text.sentences[i],&text.sentences[i+1],(len_of_txt-i)*sizeof(struct Sentence*));
            len_of_txt--;
            i--;
        }

    }
    text.n=len_of_txt;
    return text;


}

struct Text task3(struct Text text){
    int len_of_txt=text.n;

    wchar_t sym[]=L"aeyuioEUIOAуеёэоаыяиюЮИЯЫАОЭЁЕУ";
    wchar_t alphabet[]=L"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNMйцукенгшщзхъфывапролджэёячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЁЯЧСМИТЬБЮ";

    for(int i=0;i<len_of_txt;i++) {
        int full_len = text.sentences[i]->len;
        wchar_t str[full_len +2];
        wchar_t str_a[full_len+2];
        wcscpy(str, text.sentences[i]->words);
        wcscpy(str_a, text.sentences[i]->words);

        wchar_t *tr;
        wchar_t *token = wcstok(str, L" ,.", &tr);

        wchar_t *list_of_words[full_len];
        int kol = 0;
        while (token != NULL){
            list_of_words[kol++] = token;
            token = wcstok(NULL, L" ,.", &tr);
        }

        wchar_t *token_a = wcstok(str_a, alphabet, &tr);
        wchar_t *list_of_sp[full_len];
        int kol_sp = 0;
        while (token_a != NULL){
            list_of_sp[kol_sp++] = token_a;
            token_a = wcstok(NULL, alphabet, &tr);
        }

        wchar_t change[full_len +2];

        for(int q=0;q<kol-1;q++){
            for(int w=q;w<kol;w++){
                wchar_t *vowels_a,*vowels_b;



                wchar_t *word_a=list_of_words[q];
                wchar_t *word_b=list_of_words[w];



                vowels_a = wcspbrk (word_a, sym);

                int kol_a=0,kol_b=0;

                while (vowels_a != NULL)
                {
                    kol_a++;
                    vowels_a = wcspbrk (vowels_a+1,sym);
                }


                vowels_b = wcspbrk (word_b, sym);
                while (vowels_b != NULL)
                {
                    kol_b++;
                    vowels_b = wcspbrk (vowels_b+1,sym);
                }

                if(kol_b>kol_a){
                    list_of_words[q]=word_b;
                    list_of_words[w]=word_a;


                }


            }

        }


        wchar_t change_now[full_len +2];
        if(kol==kol_sp && kol>1){
            wcscpy(change,list_of_words[0]);
            wcscat(change,list_of_sp[0]);

            for(int k=1;k<kol;k++){
                int len_sym= wcslen(list_of_words[k]), len_sep= wcslen(list_of_sp[k]);
                wchar_t pair[len_sym+len_sep+1];
                wcscpy(pair,list_of_words[k]);
                wcscat(pair,list_of_sp[k]);

                wcscat(change,pair);

            }

            wcscpy(text.sentences[i]->words,change);

        } else{
            wcscpy(change,list_of_words[0]);
            wcscat(change,list_of_sp[1]);

            for(int k=1;k<kol;k++){
                int len_sym= wcslen(list_of_words[k]), len_sep= wcslen(list_of_sp[k+1]);

                wchar_t pair[len_sym+len_sep+1];

                wcscpy(pair,list_of_words[k]);
                wcscat(pair,list_of_sp[k+1]);
                //wprintf(L"'%ls'\n",pair);
                wcscat(change,pair);
                //wprintf(L"%d %d\n",len_sym,len_sep);
                //wcscat(change,wcscat(list_of_words[k],list_of_sp[k]));
                //wprintf(L"STR=='%ls'\n",change);
            }

            wcscpy(change_now,list_of_sp[0]);
            wcscat(change_now,change);
            wcscpy(text.sentences[i]->words,change_now);

        }



    }


    return text;
}




struct Arr{
    int kol_repeat;
    wchar_t* word;
    int len_rep;
};

struct Arr** task4 (struct Text text){
    int len_of_txt=text.n;
    struct Arr** arr_get= malloc(len_of_txt*sizeof (struct Arr*));



    for(int i=0;i<len_of_txt;i++) {
        int full_len = text.sentences[i]->len;


        wchar_t* str= malloc(sizeof (wchar_t)*(full_len+2));
        wcscpy(str,text.sentences[i]->words);


        wchar_t *tr;
        wchar_t *token = wcstok(str, L" ,.", &tr);

        wchar_t *list_of_words[full_len];
        int kol = 0;
        while (token != NULL) {
            list_of_words[kol++] = token;
            token = wcstok(NULL, L" ,.", &tr);
        }


        arr_get[i]= malloc(kol*sizeof (struct Arr));


        // int max=0;
        int kol_arr=0;
        for(int q=0;q<kol;q++){
            int kol_rep=0;
            wchar_t *word_check = list_of_words[q];

            for(int w=q+1;w<kol;w++){


                if(wcscmp(word_check,list_of_words[w])==0){
                    kol_rep++;
                    memmove(&list_of_words[w],&list_of_words[w+1],(kol-w)*sizeof (wchar_t*));
                    w--;
                    kol--;
                }

            }



            arr_get[i][kol_arr].word=word_check;
            arr_get[i][kol_arr].kol_repeat=kol_rep;

            kol_arr++;






        }
        arr_get[i][0].len_rep=kol;
    }

    return arr_get;
}



