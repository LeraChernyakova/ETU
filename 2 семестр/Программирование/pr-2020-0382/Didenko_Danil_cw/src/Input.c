#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"
#include "Input.h"



int repeate(Text* text, Sentence* sent){
    for (int i = 0; i < text->count_sent; i++){
        if (!(wcscasecmp(text->text[i].sent,sent->sent))){
            return 1;
        }
    }
    return 0;
}//Используется при вводе

int correcting_sent(Sentence* sent, wchar_t* sym){
    if (*sym == '\t'){*sym = ' ';}
    if(*sym == ' '){
        if(sent->is_begin == 1){sent->is_begin = 0;sent->spaces++; return 0;}
        else if(sent->spaces == 1){return 0;}
        if(sent->sent[sent->size_sent-1] == ','){return 0;}
        sent->spaces++;
    }else if(*sym == ','){
        if (sent->sent[sent->size_sent-1] == ' '){
            sent->sent[sent->size_sent-1] = ',';//Первым незначащим символом в предложении не может быть запятая
            return 0;}
    }else if(*sym == '\n'){
        sent->spaces = 0;
        sent->ind_stop++;
        sent->is_begin = 0;
        if (sent->ind_stop == 2){return 1;}
        return 0;
    }else{
        sent->is_begin = 0;
        sent->spaces = 0;
        sent->ind_stop = 0;}
    sent->sent[sent->size_sent] = *sym;

    return 2;
}//Используется при вводе

void get_proper(Word* word){
    wchar_t* vovels = L"aeiouyAEIOUYауоыиэяюёеАУОЫИЭЯЮЁЕ";
    int begin_word = 1;
    word->up_let = 0;
    word->count_vovels = 0;
    int i = 0;
    while (word->word[i] != '\0'){
        if (begin_word == 1 && iswupper(word->word[i])){
            word->up_let = 1;
            begin_word = 0;
        }else begin_word = 0;
        int j = 0;
        while (vovels[j] != '\0'){
            if (word->word[i] == vovels[j]){
                word->count_vovels++;
                break;
            }
            j++;
        }
        i++;
    }
    word->size_word = i;
    word->is_first_rep = 1;//Используется для задачи 4, первое ли повторяющееся слово
    word->count_equal_words = 1;//Используется для задачи 4, количество повторяющихся слов, по начало 1(оно само)
}//Используется при вводе

void get_words(Sentence* sent){
    sent->count_words = 0;
    Word* tmp;
    int count_words_cur = 30;
    sent->words = (Word*)malloc(count_words_cur*sizeof(Word));
    sent->copy_sent = (wchar_t*)malloc((sent->size_sent+2)*sizeof(wchar_t));
    wcscpy(sent->copy_sent,sent->sent);//Новая строка,которую будем резать
    wchar_t* p;//Массив,в котором храним указатели на текущее место среза
    sent->words[0].word = wcstok(sent->copy_sent,L" ,.",&p);
    get_proper(&(sent->words[0]));
    int i = 0;
    while(1){
        if(sent->count_words == count_words_cur-1){
            count_words_cur+=30;
            tmp = (Word*)realloc(sent->words,count_words_cur*sizeof(Word));
            sent->words = tmp;
        }
        i++;
        sent->words[i].word = wcstok(NULL,L" ,.",&p);//Последнее слово Null всегда, но в кол-во слов в предложении не входит
        if (sent->words[i].word == NULL){break;}
        get_proper(&(sent->words[i]));
    }
    sent->count_words = i;
}

void get_sent(Sentence* sent){
    wchar_t* tmp;
    int size_sent_cur = 10;
    sent->size_sent = 0;
    sent->sent = (wchar_t*)malloc(size_sent_cur*sizeof(wchar_t));
    wchar_t sym = ' ';
    sent->spaces = 0;
    sent->ind_stop = 0;
    sent->is_begin = 1;
    while(sym != '.'){
        if(sent->size_sent == size_sent_cur-2){
            size_sent_cur+=30;
            tmp = (wchar_t*)realloc(sent->sent, size_sent_cur*sizeof(wchar_t));
            sent->sent = tmp;
        }
        sym = (wchar_t)getwchar();
        int variant = correcting_sent(sent,&sym);//Функция по форматированию предложения.
        if (variant == 0){continue;}
        else if(variant == 1){ break;}
        else if(variant == 2){ sent->size_sent++;}
    }
    if(sent->sent[sent->size_sent-2] == ' '){sent->sent[sent->size_sent-2] = '.';sent->size_sent--;}
    sent->sent[sent->size_sent] = '\0';
}//Используется при вводе

void get_text(Text* text){
    Sentence* tmp;
    int size_text = 5;
    text->count_sent = 0;
    text->text = (Sentence*)malloc(size_text*sizeof(Sentence));
    while(1){
        if(text->count_sent == size_text-1){
            size_text+=30;
            tmp = (Sentence*)realloc(text->text, size_text*sizeof(Sentence));
            text->text = tmp;
        }
        get_sent(&text->text[text->count_sent]); //Получаем структуру предложения
        if (repeate(text,&text->text[text->count_sent])){
        free(text->text[text->count_sent].sent);
        continue;}//Если предложение встречалось, не добавляем его
        if (text->text[text->count_sent].size_sent == 1 && text->text[text->count_sent].sent[0] == '.'){
        free(text->text[text->count_sent].sent);
        continue;}
        if (text->text[text->count_sent].ind_stop == 2){break;}//Условное завершение ввода
        get_words(&text->text[text->count_sent]);//Разбиваем предложение на слова
        text->text[text->count_sent].index_sent = text->count_sent;//Даем индекс предложению
        text->count_sent++;
    }
}//Используется при вводе

