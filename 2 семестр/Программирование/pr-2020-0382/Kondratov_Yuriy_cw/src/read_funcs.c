#include "read_funcs.h"

struct Sentence get_sentence() {
    struct Sentence sent;
    int sent_mem_size = SENT_STEP;
    int sent_len = 0;
    int is_final = FALSE;

    sent.sentence = calloc(sent_mem_size, sizeof(wchar_t));

    wchar_t sym;
    do {
        sym = (wchar_t) fgetwc(stdin);
        if (sym == EOINP){
            is_final = TRUE;
            break;
        }
        sent.sentence[sent_len++] = sym;
        if (sent_len == sent_mem_size - 2) {
            sent_mem_size += SENT_STEP;
            sent.sentence = realloc(sent.sentence, sent_mem_size * (sizeof(wchar_t)));
        }
    } while (sym != L'.');
    sent.sentence[sent_len] = L'\0';

    sent.sent_len = sent_len;
    sent.is_final = is_final;
    return sent;
}

struct Text get_text() {
    int text_mem_size = TEXT_STEP;
    struct Text text;
    int text_len = 0;

    text.sentences = calloc(text_mem_size, sizeof(struct Sentence));

    while (TRUE) {
        struct Sentence sentence = get_sentence();
        split(&sentence);

        int i;
        for (i = 0; i < text_len; i++) {
            if (!(wcscasecmp(text.sentences[i].first_word, sentence.first_word))) break;
        }
        if (i == text_len) {
            if (sentence.sent_len) text.sentences[text_len++] = sentence;
        }
        else{
            free(sentence.sentence);
            free(sentence.words);
            free(sentence.sent_copy);
        }

        if (sentence.is_final) break;

        if (text_len == text_mem_size - 2) {
            text_mem_size += TEXT_STEP;
            text.sentences = realloc(text.sentences, text_mem_size * (sizeof(struct Sentence)));
        }
    }

    text.text_len = text_len;
    return text;
}
