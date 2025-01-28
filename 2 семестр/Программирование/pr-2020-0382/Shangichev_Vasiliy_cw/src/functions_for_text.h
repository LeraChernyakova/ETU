#ifndef FFT
#define FFT

#include "string_structures.h"
#include "substring_struct.h"

void free_memory(struct Text* text);
void get_text(struct Text* processed_text);
void get_words(struct Text* text);
void replace_digits(struct Text* text);
void sort_words(struct Text* text);
void print_text(struct Text* text);

#endif