#include "TextMaker.h"

SENT read(){
    WORD inp_word;
    SENT inp_sent;
    int size = 100; //размер выделенной памяти для inp_word и inp_sent
    wchar_t inp;

    initializeSent(&inp_sent);
    initializeWord(&inp_word);
    inp = getwchar();
    if (inp == L'\n'){
        inp_word.word[inp_word.len++] = inp;
        inp_word.word[inp_word.len++] = L'\0';
        inp_sent.sent[0] = inp_word;
        return inp_sent;
    }
    while (inp != L'.'){
        if ((inp_word.len+5> size) || (inp_sent.len+5> size)) {
            size += 1000;
            inp_word.word = realloc(inp_word.word, size * sizeof(wchar_t));
            inp_sent.sent = realloc(inp_sent.sent, size * sizeof(WORD));
        }
        if (inp<100) {
            if (isDigit(inp)) {
                inp_sent.in++;
                //wprintf(L"%ls %d\n", inp_sent.sent[0].word, inp_sent.in);
            }
        }
        if (( inp == L'#')||( inp == L'№')){
            inp_sent.spe++;
            //wprintf(L"%ls %d\n", inp_sent.sent[0].word, inp_sent.spe);
        }
        if ((inp == L' ') || (inp == L',')){
            inp_word.word[inp_word.len++] = L'\0';
            if (inp_sent.mass < 100000000000000) {
                if (inp_word.len > 1) {
                    inp_sent.mass *= inp_word.len - 1;
                }
            }
            //wprintf(L"%ld\n", inp_sent.mass);
            inp_sent.sent[inp_sent.len++] = inp_word;
            initializeWord(&inp_word);
            inp_word.word[inp_word.len++] = inp;
            inp_word.word[inp_word.len++] = L'\0';
            inp_sent.sent[inp_sent.len++] = inp_word;
            initializeWord(&inp_word);
            inp = getwchar();
        }
        else{
            inp_word.word[inp_word.len++] = inp;
            //inp_word.word[inp_word.len++] = L'\0';
            inp = getwchar();
        }
        //wchar_t * arr = inp_word.word;
        //wprintf(L"%ls %c %c\n", arr, inp_word.word[inp_word.len - 1], inp);
    }
    inp_word.word[inp_word.len++] = L'\0';
    if (inp_sent.mass < 100000000000000) {
        if (inp_word.len > 1) {
            inp_sent.mass *= inp_word.len - 1;
        }
    }
    //wprintf(L"%lld w\n", inp_sent.mass);
    inp_sent.sent[inp_sent.len++] = inp_word;
    return inp_sent;
}

void shift(TEXT * lst, int i){
    for (int j = 0; j < lst->text[i].len; ++j) {
        free(lst->text[i].sent[j].word);
    }
    for (;i <lst->len;i++){
        lst->text[i] = lst->text[i+1];
    }
    int t = (lst->len)-1;
    free(lst->text[t].sent);
    lst->len--;
}

TEXT create_text(){
    TEXT inp_text;
    initializeText(&inp_text);
    SENT inp_sent;
    int size = 100;
    do {
        if (inp_text.len + 5 > size){
            size *= 2;
            inp_text.text = realloc(inp_text.text, size * sizeof(SENT));
        }
        inp_sent = read();
        inp_text.text[inp_text.len++] = inp_sent;
        //wprintf(L"%d\n", inp_text.len);
        for (int i = 0; i < inp_sent.len; i++){
            //wprintf(L"%ls %d\n", inp_sent.sent[i], inp_text.len);
        }
    }while (inp_sent.sent[0].word[0] != L'\n');

    for (int i = 0; i < inp_text.len - 2; i++){
        for (int j = i+1; j < inp_text.len - 1;){
            //wprintf(L"%d %d\n", inp_text.text[i].len, inp_text.text[j].len);
            if (inp_text.text[i].len == inp_text.text[j].len){
                int help = 0;
                for (int k = 0; k < inp_text.text[i].len; k++){
                    if (wcscasecmp(inp_text.text[i].sent[k].word,inp_text.text[j].sent[k].word)){
                        help++;
                    }
                }
                if (help == 0){
                    shift(&inp_text, j);
                } else j++;
            }
            else{
                j++;
            }
        }
    }
    return inp_text;
}
