struct Sentence{
    wchar_t **words;
    wchar_t *phrase;
    int lent, right, countwords, maxword;
};

struct Text{
    struct Sentence* text;
    int len;
};
