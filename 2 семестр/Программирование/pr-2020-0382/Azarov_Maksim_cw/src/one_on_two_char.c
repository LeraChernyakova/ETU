
#include "top_header.h"
#include "primitiv_func.h"
#include "one_on_two_char.h"

void str_append(Sentence* sent,int num,wchar_t* substr ){
    wchar_t *temp_sent;
    int len_substr= (int)wcslen(substr) ,i,j;


    //перевыделение памяти
    while(sent->len >= sent->avlb_len - len_substr-1){//-1 на всякий случай
        sent->avlb_len = sent->avlb_len + BASIC_LEN_SENT;
        temp_sent = realloc(sent->str, sent->avlb_len*sizeof(wchar_t));

        if (temp_sent == NULL) {
            free(sent->str);
            fprintf(stderr, "Ошибка перевыделения памяти для sent");
            exit(1);
        } else {
            sent->str = temp_sent;
        }
    }

    //сдвиг
    for(j = 0 ; j < len_substr;j++) {
        for (i = sent->len; i >=
        num + j; i--) {
            sent->str[i + 1] = sent->str[i];
        }
        sent->len++;
    }

    //вставка
    for(i = num ; i < num+len_substr ; i++){
        sent->str[i] = substr[i-num];
    }
}



Text replace_substr(Text _text){
    int i,j,k;
    wchar_t  dict[][2][3] ={{L"а",L"бв"},{L"е",L"ёж"},{L"ё",L"жз"},{L"и",L"йк"},{L"о",L"пр"},//руский
                          {L"у",L"фх"},{L"ы",L"ьэ"},{L"э",L"юя"},{L"ю",L"яа"},{L"я",L"аб"},
                          {L"А",L"БВ"},{L"Е",L"ЁЖ"},{L"Ё",L"ЖЗ"},{L"И",L"ЙК"},{L"О",L"ПР"},
                          {L"У",L"ФХ"},{L"Ы",L"ЬЭ"},{L"Э",L"ЮЯ"},{L"Ю",L"ЯА"},{L"Я",L"АБ"},
                          {L"a",L"bc"},{L"e",L"fg"},{L"i",L"jk"},{L"o",L"pq"},{L"u",L"vw"},//английский
                          {L"y",L"za"},
                          {L"A",L"BC"},{L"E",L"FG"},{L"I",L"JK"},{L"O",L"PQ"},{L"U",L"VW"},//английский
                          {L"Y",L"ZA"}};


    int len_dict = sizeof (dict)/(sizeof (wchar_t)*3*2);

    for (i = 0 ; i < _text.size; i++){   //в каждом предложение
        for (j = 0; j < _text.sents[i].len; j++){    //каждая буква
            for(k = 0; k < len_dict ;k++){     //сравнивается с каждым эл dict
                if (_text.sents[i].str[j] == dict[k][0][0]){
                
                    delt_char(j,_text.sents[i].str);
                    _text.sents[i].len--;
                    
                    str_append(&_text.sents[i],j,dict[k][1]);
                    j++;
                }
            }
        }
    }

    return _text;
}
