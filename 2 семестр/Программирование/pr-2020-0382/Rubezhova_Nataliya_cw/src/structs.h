#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    wchar_t* buf;
    int leng_word;
}Word;

typedef struct {
    Word* buf_words;
    int leng_sent;
    wchar_t* str_sent;
    int leng_str;//считает длину строки с нулевым символом в конце
    int* buf_codes_symb;
    int leng_buf_codes_symb;
}Sentence;

typedef struct {
    Sentence* buf_sents;
    int leng_text;
}Text;
#endif
