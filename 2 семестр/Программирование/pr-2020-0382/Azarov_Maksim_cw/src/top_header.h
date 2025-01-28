#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>


#define BASIC_LEN_SENT 50
#define BASIC_LEN_TEXT 20
#define MAX_LEN_WORD 100


//создание типов Sentence, Text

struct Sentence{
    wchar_t *str ;
    int len,avlb_len,  group_anagram; //group_anagram = 0 -> не анаграмма
    int vol_upper;//количество сиволов верхнего регистра

};
typedef struct Sentence Sentence ;

struct Text{
    Sentence *sents;
    int size , avlb_size;
    int volume_gr_anagram; // количество групп анаграмм
};
typedef struct Text Text;




