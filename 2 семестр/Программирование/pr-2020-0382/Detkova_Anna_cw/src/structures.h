struct Sentence{
    wchar_t* cur_sentence;
    int len, num_words;
    wchar_t ** words, * dots;
};

struct Text{
    struct Sentence *sentence;
    int sent_count;
};
