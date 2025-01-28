#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <stdlib.h>
#include "structs.h"
#include "text_func.h"

#define BUFFER 100

struct Text get_text(){
    struct Text inp_text;
    int text_buffer = BUFFER, words_buffer = BUFFER, sep_buf = BUFFER;
    int words_in_sent = 0, letters_in_sent = 0, num_of_sent = 0, letters_in_word = 0;
    wchar_t *word; //собираются слова
    inp_text.sentences  = malloc(text_buffer * sizeof(struct Sentence));
    wchar_t inp_sym;
    int point = 1, flag2 = 1, same = 0;
    while(point == 1){
        inp_sym = getwchar();
        if (inp_sym == L'\n') {
            point = 0;
            break;
        }
        struct Sentence sentence;
        sentence.words = malloc(words_buffer * sizeof(wchar_t*));
        sentence.separator = malloc(sep_buf * sizeof(wchar_t));
        sentence.num_of_words = 0;
        sentence.len_of_3 = 0;
        while(inp_sym != L'.') {
            word = malloc(words_buffer * sizeof(wchar_t));
            while (inp_sym != L' ' && inp_sym != L',' && inp_sym != L'.') { //обработка слова
                word[letters_in_word] = inp_sym;
                letters_in_word++;
                if (letters_in_word + 5 == words_buffer){ //память для счит. слова
                    word = realloc(word, words_buffer * sizeof(wchar_t));
                    sentence.words = realloc(sentence.words, words_buffer  * sizeof(wchar_t*));
                    words_buffer += BUFFER;
                }
                letters_in_sent++;
                inp_sym = getwchar();
            }
            word[letters_in_word] = L'\0';
            sentence.words[words_in_sent] = word;
            if (words_in_sent == 2) //ищем длину 3 слова
                sentence.len_of_3 = letters_in_word;
            letters_in_word = 0;
            sentence.separator[words_in_sent] = inp_sym;
            if (words_in_sent + 2 == sep_buf){
                sentence.separator = realloc(sentence.separator, sep_buf * sizeof(wchar_t));
                sep_buf += BUFFER;
            }
            letters_in_sent++;
            words_in_sent++;
            if (inp_sym != L'.' && inp_sym != L'\n') {
                inp_sym = getwchar();
            }
            else break;
        }
        sentence.num_of_words = words_in_sent;
        words_in_sent = 0;
        flag2 = 0;
        same = 0;
        for (int i = 0; i < num_of_sent; i++){
            struct Sentence prev = inp_text.sentences[i];
            for (int j = 0; j < prev.num_of_words; j++){
                if (prev.num_of_words != sentence.num_of_words)
                    break;
                if (prev.separator[j] == sentence.separator[j])
                    flag2++;
                for (int k = 0; k < wcslen(prev.words[j]); k++)
                    if (towlower(prev.words[j][k]) == towlower(sentence.words[j][k])){
                        flag2++;
                    }
            }
            if (flag2 == letters_in_sent) {
                same = 1;
                break;
            }
            flag2 = 0;
        }
        letters_in_sent = 0;
        if (same == 0) {
            inp_text.sentences[num_of_sent] = sentence;
            num_of_sent++;
            if (num_of_sent + 2 == text_buffer) {
                inp_text.sentences = realloc(inp_text.sentences, text_buffer * sizeof(struct Sentence));
                text_buffer += BUFFER;
            }
        }
    }
    inp_text.len_text = num_of_sent;
    return inp_text;
}

void print_text(struct Text inp_text){
    for (int i = 0; i < inp_text.len_text; i++) {
        for (int j = 0; j < inp_text.sentences[i].num_of_words; j++){
            wprintf(L"%ls%c", inp_text.sentences[i].words[j], inp_text.sentences[i].separator[j]);
        }
    }
    wprintf(L"\n");
}