#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"
#include "processing_funcs.h"

#define TRUE 1
#define FALSE 0
#define SENT_STEP 50
#define TEXT_STEP 5
#define EOINP L'\0'

struct Sentence get_sentence();

struct Text get_text();

