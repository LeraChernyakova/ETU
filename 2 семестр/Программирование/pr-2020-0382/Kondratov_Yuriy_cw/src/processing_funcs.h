#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"

#define TRUE 1
#define FALSE 0

void split(struct Sentence *sent);

int last_words_cmp(const void *a, const void *b);
