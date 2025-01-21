#include <wchar.h>
#pragma once
struct Sentence
{
    wchar_t* string;
    int size, len, count, count_upper_symbol;
};

struct Text
{
    struct Sentence** sentences;
    int size;
    int len;
};
