struct Sentence{
    wchar_t **words;
    wchar_t *separator;
    int num_of_words;// количество слов в предложении
    int len_of_3; //длина третьего слова

};

struct Text{
    struct Sentence *sentences;
    int len_text;
};
