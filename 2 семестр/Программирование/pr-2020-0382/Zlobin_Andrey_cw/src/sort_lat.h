#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include "text_struct.h"

int compare_sentences(const void * s1, const void * s2);
struct Text sort_lat(struct Text text);
