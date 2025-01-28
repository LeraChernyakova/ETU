#ifndef INPUT_F_H
#define INPUT_F_H

#define SIZE 50
wchar_t get_Word(wchar_t c,Word* word_ptr);
wchar_t get_Sent(wchar_t sym, Sentence* sent_ptr);
void get_Text(wchar_t c, Text* inp_p);
void get_str_sent(Text* text_p);
void check_repeat(Text* text_p,Sentence* sent_p);
#endif
