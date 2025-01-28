#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#ifndef END_WERS_KURS_J_H
#define END_WERS_KURS_J_H
struct Words {
    wchar_t * word;
    int len; // длина слова
};

typedef struct Words WORD;

struct Sentence {
    WORD * sent;
    int spe; // есть ли специальныеслимволы в предложении
    int in; // есть ли числа в предложении
    int len; // количество слов в предложении
    long long int mass;
};

typedef struct Sentence SENT;

struct Text {
    SENT * text;
    int len; // количество предложений в тексте
};

#endif

typedef struct Text TEXT;
void initializeWord(WORD * lst);
void initializeSent(SENT * lst);
void initializeText(TEXT * lst);
int isDigit(char qwes);

