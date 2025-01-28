#pragma once

struct Sentence {
    wchar_t *sentence;
    wchar_t *sent_copy;
    wchar_t **words;
    wchar_t *first_word;

    int is_final;
    int sent_len;
    int words_count;
};

struct Text {
    struct Sentence *sentences;
    int text_len;
};
