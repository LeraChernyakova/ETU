#pragma once
#include <wchar.h>


struct Sentence{
    wchar_t* sent;
};
typedef struct Sentence Sentence;

struct Text{
    Sentence* doc;
    int text_size;
};
typedef struct Text Text;
