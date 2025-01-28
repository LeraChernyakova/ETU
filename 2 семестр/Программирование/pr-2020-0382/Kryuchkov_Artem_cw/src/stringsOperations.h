#pragma once

#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include "input.h"

#include "textStructures.h"

int countWords(struct Sentence s);

struct Text deleteSentence(struct Text text, int indexToDelete);

struct Text deleteRepeatedSentences(struct Text text);

struct Text deleteBigSentences(struct Text text);

struct Text changeEnding(struct Text text);

int compareSentencesByWords(const void *ss1, const void *ss2);