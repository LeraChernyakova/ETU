#pragma once

#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#include "textStructures.h"

#define INIT 20 // дополнительный размер выделяемый при заполнении

struct Sentence *readSentence();

struct Text readText();
