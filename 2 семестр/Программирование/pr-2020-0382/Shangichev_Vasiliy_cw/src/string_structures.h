#ifndef SS
#define SS
#include <wchar.h>

struct Word {
    wchar_t* symbols;
    int number_of_latin_letters;
};

struct Sentence {
    struct Word* words;
    wchar_t* chars;
    int words_number;
    wchar_t* separators;
};

struct Text {
    struct Sentence* sentences;
    int text_len;
};

#endif

