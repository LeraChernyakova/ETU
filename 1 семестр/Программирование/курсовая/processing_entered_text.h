struct Sentence{
    wchar_t* str;
    int len; 
    int size;
    int words;
};

struct Text{
    struct Sentence** sent;
    int size;
    int cnt_sent;
};

struct Sentence* readSentence();

struct Text readText();

struct Text del_repeat_sent(struct Text text);

void print_text(struct Text* text);

void free_text(struct Text* text);

