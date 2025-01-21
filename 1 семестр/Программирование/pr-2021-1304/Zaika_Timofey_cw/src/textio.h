
struct Sentence{
	wchar_t *str;
	int size;
};

struct Text{
	struct Sentence **sents;
	int n;
	int size;
};

struct Text readText();
struct Sentence readSentence();
void changed_text(struct Text *text);
void print_text(struct Text *text);
void free_text(struct Text *text);