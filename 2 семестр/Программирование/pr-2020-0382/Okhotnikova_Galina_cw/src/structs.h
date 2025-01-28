struct  Sentence {
    wchar_t* s;
    wchar_t* time_s;
    int len_s, count_k;
    long int diff_t;
};

struct Text {
    struct Sentence* newtxt;
    int len_t;
};
