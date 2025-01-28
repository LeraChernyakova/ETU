#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"
#include "task_4.h"

void task_4(Text* text){
    for(int i = 0;i < text->count_sent; i++){
        for(int j = 0; j < text->text[i].count_words; j++){
            if (text->text[i].words[j].is_first_rep){//Если таких слов не было, то ищем, иначе нет
                for (int k = j+1;k < text->text[i].count_words;k++){
                    if(!wcscmp(text->text[i].words[j].word,text->text[i].words[k].word)){
                        text->text[i].words[k].is_first_rep = 0;//Найденному слову присваиваем значение, что оно уже встречалось в предложении
                        text->text[i].words[j].count_equal_words++;//Увеличиваем кол-во одинаковых слов
                    }
                }
            }
        }
    }
}

