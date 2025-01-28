#include <locale.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "structures.h"
#include "del_sent.h"
#include "sort_len_word.h"
#include "search.h"
#include "less_order.h"
#include "cmp.h"
#include "cmp2.h"



int main(){
    setlocale(LC_ALL, "");
    
    wprintf(L"Вас приветствует программа, которая обрабатывает текст!\n"
             "Введите текст, который нужно отредактировать.\n"
             "(Чтобы закончить ввод, следует нажать enter)\n");
    
    wchar_t symbol = L'0';
    int flag = 1, txt_buf = 10;
    struct Text text;
    
    text.sent_count = 0;
    text.sentence = (struct Sentence*)malloc(txt_buf * sizeof(struct Sentence));
    
    while(flag == 1){
    
        symbol = getwchar();
        
        if (symbol == L'\n'){
            flag = 0;
            break;
        }
        
        int buffer = 20;
        struct Sentence sentence;
        sentence.cur_sentence = (wchar_t*)malloc(buffer * sizeof(wchar_t));
        sentence.len = 0;
        
        
        int num_letters = 0, wordsize = 20, sentsize = 10;
        sentence.num_words = 0;
        wchar_t* word = malloc(wordsize * sizeof(wchar_t));
        sentence.words = malloc(sentsize * sizeof(wchar_t*));
        sentence.dots = malloc(sentsize * sizeof(wchar_t));
        
        while(symbol != L'.'){
        
            sentence.cur_sentence[sentence.len] = symbol;
            sentence.len ++;
            
            if ((symbol != L',') && (symbol != L' ')){
                word[num_letters] = symbol;
                num_letters ++;
                if (num_letters + 2 == wordsize){
                    wordsize = wordsize + 10;
                    word = realloc(word, wordsize * sizeof(wchar_t));
                }
            }
            else{
                word[num_letters] = L'\0';
                
                if (sentence.num_words + 2 == sentsize){
                    sentsize = sentsize + 5;
                    sentence.words = realloc(sentence.words, sentsize * sizeof(wchar_t*));
                    sentence.dots = realloc(sentence.dots, sentsize * sizeof(wchar_t));
                }
                
                sentence.words[sentence.num_words] = word;
                sentence.dots[sentence.num_words] = symbol;
                sentence.num_words ++;
                
                word = malloc(wordsize * sizeof(wchar_t));
                num_letters = 0;
                
            }
            
            if (sentence.len + 2 == buffer){
                buffer = buffer + 20;
                sentence.cur_sentence = realloc(sentence.cur_sentence, buffer * sizeof(wchar_t));
            }
            symbol = getwchar();
        }
        
        word[num_letters] = L'\0';
        
        sentence.words[sentence.num_words] = word;
        sentence.dots[sentence.num_words] = symbol;
        sentence.num_words ++;
        sentence.dots[sentence.num_words] = '\0';
        
        sentence.cur_sentence[sentence.len] = symbol;
        sentence.len ++;
        
        sentence.cur_sentence[sentence.len] = '\0';
        
        int sign = 0;
        
        for (int i = 0; i < text.sent_count; i ++)
            if (sentence.len == text.sentence[i].len){
                int k = 0;
                for (int j = 0; j < sentence.len; j ++){
                    if (tolower(sentence.cur_sentence[j]) == tolower(text.sentence[i].cur_sentence[j]))
                        k ++;
                }
                if (k == sentence.len)
                    sign = 1;
                }
        
        if (sign == 0){
            text.sentence[text.sent_count] = sentence;
            text.sent_count ++;
        }
        
        if (text.sent_count == txt_buf){
            txt_buf = txt_buf + 10;
            text.sentence = realloc(text.sentence, txt_buf * sizeof(struct Sentence)); 
        }
                   
    }
    
    int a;
    
    wprintf(L"Текст считан, выберете дальнейшие действия с программой:\n"
            "Введите '1', если хотите вывести все предложения, в которых каждое слово удовлетворяет введенной строке-условию.\n"
            "Введите '2.', если хотите отсортировать предложения по средней длине слов в предложении.\n"
            "Введите '3.', если хотите преобразовать предложения так, чтобы слова располагались в порядке уменьшения длины слова.\n"
            "Введите '4.', если хотите удалить все предложения, в котором больше 5 или меньше 2 слов.\n"
            "Введите '5.', если не нужно выполнять никаких действий.\n");
    
    wscanf(L"%d\n", &a);
    
    switch (a){
    case 1:
        wprintf(L"Введите строку-условие, ввод завершится после нажатия клавиши enter\n"
                 "Помните!\n"
                 "Что в сроке-условии может быть один символ * и сколь угодно много символов?.\n");
        struct Text result_text;
        int buf = 10, cur_size = 0;
        wchar_t* str_for_search = malloc(buf * sizeof(wchar_t));
        wchar_t ch = getwchar();
        while (ch != '\n'){
            str_for_search[cur_size] = ch;
            cur_size ++;
            if (cur_size + 2 == buf){
                buf = buf + 5;
                str_for_search = realloc(str_for_search, buf * sizeof(wchar_t));
            }
            ch = getwchar();
        }
        str_for_search[cur_size] = '\0';
        
        result_text = search(&text, &str_for_search);
        for (int i = 0; i < result_text.sent_count; i ++)
            wprintf(L"%ls", result_text.sentence[i].cur_sentence);
        break;
    case 2:
        sort_len_word(&text);
        for (int i = 0; i < text.sent_count; i ++)
            wprintf(L"%ls", text.sentence[i].cur_sentence);
        break;
    case 3:
        for (int i = 0; i < text.sent_count; i ++){
            less_order(&text.sentence[i]);
            wprintf(L"%ls", text.sentence[i].cur_sentence);
        }
        break;
    case 4:
        delete_sentences(&text);
        for (int i = 0; i < text.sent_count; i ++)
            wprintf(L"%ls", text.sentence[i].cur_sentence);
        break;
    case 5:
        for (int i = 0; i < text.sent_count; i ++)
            wprintf(L"%ls", text.sentence[i].cur_sentence);
        break;
    }
    
    for (int i = 0; i < text.sent_count; i ++){
        for(int j = 0; j < text.sentence[i].num_words; j ++){
            free(text.sentence[i].words[j]);
        }
        free(text.sentence[i].words);
        free(text.sentence[i].dots);
    }
    free(text.sentence);
    
    return 0;
}

