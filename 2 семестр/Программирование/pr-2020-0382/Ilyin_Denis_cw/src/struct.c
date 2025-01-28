#include "struct.h"

void initializeWord(WORD * lst){
    lst->word = malloc(100 * sizeof(wchar_t));
    lst->len = 0;
}

void initializeSent(SENT * lst){
    lst->sent = malloc(100 * sizeof(WORD));
    lst->len = 0;
    lst->in = 0;
    lst->spe = 0;
    lst->mass = 1;
}

void initializeText(TEXT * lst){
    lst->text = malloc(100 * sizeof(SENT));
    lst->len = 0;
}

int isDigit(char qwes){
    if ((qwes >= '0') && (qwes <= '9')) {
        return 1;
    } else return 0;
}
