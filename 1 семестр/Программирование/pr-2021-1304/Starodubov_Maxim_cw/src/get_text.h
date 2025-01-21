int get_text(struct Text* output);
int get_sentence(struct Sentence* output);
int get_content(wchar_t** string);
void remove_spaces(wchar_t* string);
int sp_symbols_detector(wchar_t* string);
int cirillic_characters_counter(wchar_t* string);