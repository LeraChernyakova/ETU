#pragma once
struct Sentence {
    wchar_t *words;
    int size;
    int n;
};
struct Text {
    struct Sentence **sentences;
    int size;
    int n;
};
