#pragma once

struct  Sentence {
    wchar_t* sentence;
    wchar_t** words;
    int count_w;
    int* len_w;
    int len_s;
    int size_sent;
    int final;
};

struct Text {
    struct Sentence* sentences; //указатель на массив со структурами
    int len_t;
    int size_text;
};
