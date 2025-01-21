#include <wchar.h>
#include <wctype.h>
#include <locale.h>

struct Sentence 
{
	wchar_t* content;
	int number_of_cirillic_characters;
	int are_there_sp_symbols;
	int size;

};

struct Text 
{
	struct Sentence* content;
	int size;

};
