
#include "top_header.h"
#include "primitiv_func.h"
#include "swap_word.h"




Sentence  find_and_swap_word(Sentence sent , wchar_t* word_old, wchar_t* word_new){
    int word_old_len = (int)wcslen(word_old) ;
    int word_new_len = (int)wcslen(word_new) ;
    int i,numb;//номер вхождения в строку
    wchar_t* p;//указатель на вхождение подстроки в строку
    Text arr_words;

    //удаляем \n в крнце слов

    p = wcsstr(sent.str,word_old);


    if (p == NULL){
        return sent;
    }
    else{
        while(p != NULL){
            numb = p-sent.str;
            if(numb == 0 ) {
                if((sent.str[word_old_len]==' ')||(sent.str[word_old_len]==',')||(sent.str[word_old_len]=='.')||(sent.str[word_old_len]=='\n')) {
                
                    //удаляем слово
                    for (i = 0; i < word_old_len; i++) {
                        delt_char(numb, sent.str);
                    }
                    sent.len -= word_old_len;
                    //вставляем слово
                    sent = add_substr(sent, numb, word_new);
		     
		     	
                    p = wcsstr(sent.str+numb, word_old);
                } 
                else{
                    p = wcsstr(sent.str+numb+word_old_len, word_old);
                }
            }
            else {
                if(((sent.str[numb-1]==' ')||(sent.str[numb-1]==',')||(sent.str[numb-1]=='\n'))&&((sent.str[numb+word_old_len]==' ')||(sent.str[numb+word_old_len]==',')||(sent.str[numb+word_old_len]=='.')||(sent.str[numb+word_old_len]=='\n'))){
                
                    //удаляем слово
                    for (i = 0; i < word_old_len; i++) {
                        delt_char(numb, sent.str);
                    }
                    sent.len -= word_old_len;
                    //вставляем слово
                    sent = add_substr(sent, numb, word_new);
		     
                    p = wcsstr(sent.str+numb, word_old);
                } 
                else{
                    p = wcsstr(sent.str+numb+word_old_len, word_old);
                }
            }
        }
        return sent;
    }
}





Text cut_sent( Sentence sent){
    Text arr_words;
    wchar_t * temp_sent;
    Sentence* temp_text;
    int i,in_word = 0,numb_word = -1;

    //выделение памяти
    arr_words.avlb_size = BASIC_LEN_TEXT;
    arr_words.sents = malloc(sizeof ( Sentence)*arr_words.avlb_size);
    arr_words.size = 0;


    for(i = 0; i < sent.len ; i++){
        //проверка на нахождении в слове
        if ((sent.str[i] != ' ')&&(sent.str[i] != '\n')&&(sent.str[i] != '.')&&(sent.str[i] != ',')&&(sent.str[i] != '\0')){
            if (in_word == 0){
                if (numb_word != -1) {arr_words.sents[numb_word].str[arr_words.sents[numb_word].len] = '\0';}

                arr_words.size += 1;
                numb_word +=1;
                if (arr_words.size >= arr_words.avlb_size) {

                    arr_words.avlb_size = arr_words.avlb_size + BASIC_LEN_TEXT;
                    temp_text = realloc(arr_words.sents, arr_words.avlb_size*sizeof(Sentence));

                    if (temp_text == NULL) {
                        for (i = 0; i < arr_words.size; i++) {
                            free(arr_words.sents[i].str);
                        }
                        free(arr_words.sents);
                        fprintf(stderr, "Ошибка перевыделения памяти для Text");
                        exit(1);
                    } else {
                        arr_words.sents = temp_text;
                    }
                }

                //выделение памяти для нового слова
                arr_words.sents[numb_word].avlb_len = BASIC_LEN_SENT;
                arr_words.sents[numb_word].str = malloc(sizeof (wchar_t)*arr_words.sents[numb_word].avlb_len) ;
                arr_words.sents[numb_word].len = 0;
            }
            in_word = 1;
        }
        else{
            in_word = 0;
        }

        //добавление символа
        if (in_word == 1){
            if (arr_words.sents[numb_word].len  >= arr_words.sents[numb_word].avlb_len - 1) {

                arr_words.sents[numb_word].avlb_len = arr_words.sents[numb_word].avlb_len + BASIC_LEN_SENT;
                temp_sent = realloc(arr_words.sents[numb_word].str, arr_words.sents[numb_word].avlb_len*sizeof(wchar_t));

                if (temp_sent == NULL) {
                    free(arr_words.sents[numb_word].str);
                    fprintf(stderr, "Ошибка перевыделения памяти для sent");
                    exit(1);
                } else {
                    arr_words.sents[numb_word].str = temp_sent;
                }
            }
            arr_words.sents[numb_word].str[arr_words.sents[numb_word].len] = sent.str[i];
            arr_words.sents[numb_word].len++;

        }


    }
    return arr_words;
}




Sentence add_substr(Sentence sent , int numb , wchar_t* word) {
    wchar_t *temp_sent;
    int word_len = (int) wcslen(word), i, j;



    //перевыделение памяти
    if (sent.len >= sent.avlb_len - 1 - word_len) {

        sent.avlb_len = sent.avlb_len + word_len + 2;
        temp_sent = realloc(sent.str, sent.avlb_len * sizeof(wchar_t));

        if (temp_sent == NULL) {
            free(sent.str);
            fprintf(stderr, "Ошибка перевыделения памяти для sent");
            exit(1);
        } else {
            sent.str = temp_sent;
        }
    }

    for (i = 0; i < word_len; i++) {
        for (j = sent.len; j >= numb+i ; j--) {
            sent.str[j+1] = sent.str[j];

        }
        sent.str[numb+i] = word[i];
        sent.len++;
    }

    return sent;

}
