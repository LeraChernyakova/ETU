wchar_t* first_word(struct Sentence *line);

wchar_t* last_word(struct Sentence *line);

int is_alright(struct Sentence* line);

struct Text* delete_lines(struct Text* text);

struct Sentence* find_and_change(struct Sentence* line);

struct Text* change_substrings(struct Text* text);
