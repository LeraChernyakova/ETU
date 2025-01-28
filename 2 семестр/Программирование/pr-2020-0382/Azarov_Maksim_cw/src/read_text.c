#include "top_header.h"
#include "read_text.h"
#include "primitiv_func.h"


Sentence get_sent(int *ext){

    Sentence sent = { .len = 0};

    wchar_t *temp_sent;
    wchar_t ch = 0, temp_ch;
    int in_sent = 0;

    sent.avlb_len = BASIC_LEN_SENT;
    sent.str = mem_alloc(sent.avlb_len , sizeof(wchar_t));


    while (ch != '.'){
        temp_ch = ch;
        ch = getwchar();

        if ((ch == '\n')&&(temp_ch == '\n')){
            *ext = 1;
            return sent;
        }

        if (sent.len  >= sent.avlb_len - 1) {

            sent.avlb_len = sent.avlb_len + BASIC_LEN_SENT;
            temp_sent = realloc(sent.str, sent.avlb_len*sizeof(wchar_t));

            if (temp_sent == NULL) {
                free(sent.str);
                fprintf(stderr, "Ошибка перевыделения памяти для sent");
                exit(1);
            } else {
                sent.str = temp_sent;
            }
        }

        sent.str[sent.len++] = ch;

    }
    sent.str[sent.len] = '\0';


    return sent;
}




Text read_text(){

    Text _text = { .size = 0};
    Sentence *temp_text;
    Sentence temp_sent;
    int ext = 0,i;



    _text.avlb_size = BASIC_LEN_TEXT;
    _text.sents = mem_alloc(_text.avlb_size,sizeof(Sentence));

    while (ext == 0){

        //проверка на свободное место
        if (_text.size >= _text.avlb_size) {

            _text.avlb_size = _text.avlb_size + BASIC_LEN_TEXT;
            temp_text = realloc(_text.sents, _text.avlb_size*sizeof(Sentence));

            if (temp_text == NULL) {
                for (i = 0; i < _text.size; i++) {
                    free(_text.sents[i].str);
                }
                free(_text.sents);
                fprintf(stderr, "Ошибка перевыделения памяти для Text");
                exit(1);
            } else {
                _text.sents = temp_text;
            }
        }


        //_text.sents[_text.size] = get_sent(&ext);
        //проверка на повтор
        temp_sent = get_sent(&ext);

        if (ext == 0) {
            if (!in_text(temp_sent, _text)) {
                _text.sents[_text.size++] = temp_sent;
            }
        }
    }

    return _text;
}



int in_text(Sentence sent , Text _text){

    for (int i = 0 ; i<_text.size ; i++){
        if (!wcscasecmp(sent.str,_text.sents[i].str)){
            return 1;
        }
    }

    return 0;
}

