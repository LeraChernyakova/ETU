#pragma once
#include "structures.h"
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

Text shift_text(Text test_text,int count, int* del);

Text DoSentencesUnique(Text FixText);

int upsortcmp(const void* a, const void* b);

Text UpSort(Text SortText);

Sentence Shift_Sent(Sentence sc,int* beg,int count,int shift_size, wchar_t sym);

Text ChangeSpecSym(Text RedText);

Text Delete_3_consonant_in_a_row(Text RedactText);
