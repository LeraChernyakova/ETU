#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#define STAND_TXT 30
#define STAND_SENT 100
#define STAND_WORD 50
struct Sentence{
	wchar_t *s;
	int size;
};

struct Text{
	struct Sentence **t;
	int size;
	int len;
	
};
struct Word{
	wchar_t* w;
	int begin;
	int end;
};
