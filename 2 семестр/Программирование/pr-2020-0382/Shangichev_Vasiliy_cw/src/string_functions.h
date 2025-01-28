#ifndef SF
#define SF
#include "string_structures.h"
#include "substring_struct.h"

void get_substrings(struct Substrings* substrings, struct Text* text);
int compare_words(const void* a, const void* b);
int get_number_of_latin_letters(struct Word word);
void set_k(struct Text* text);
#endif