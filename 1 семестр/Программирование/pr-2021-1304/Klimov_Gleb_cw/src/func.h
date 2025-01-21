#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>


struct Text
{
wchar_t **t;
int size; 
};
struct Sentence{
wchar_t *s;
};
struct Text read();
void choice();
wchar_t ** delete_copy(struct Text parm);
void data(struct Text parm);
void delete(struct Text parm);
void reverse(struct Text parm);
void sort(struct Text parm);

