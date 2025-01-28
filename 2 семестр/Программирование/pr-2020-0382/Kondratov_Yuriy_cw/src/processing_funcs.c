#include "processing_funcs.h"

void split(struct Sentence *sent) {
    wchar_t *sent_copy = calloc(sent->sent_len, (sizeof(wchar_t)) + 1);
    wcscpy(sent_copy, sent->sentence);

    wchar_t **words = calloc(sent->sent_len, sizeof(wchar_t *));
    wchar_t *word;
    wchar_t *first_word;
    wchar_t *tmp;

    int i = 0;
    word = wcstok(sent_copy, L", .\n\t", &tmp);
    if (word != NULL) first_word = sent->sentence + (word - sent_copy);
    else first_word = sent->sentence + wcslen(sent->sentence) - 1;
    while (word != NULL) {
        words[i++] = word;
        word = wcstok(NULL, L", .\n\t", &tmp);
    }

    sent->sent_copy = sent_copy;
    sent->words = words;
    sent->words_count = i;
    sent->first_word = first_word;
}

int last_words_cmp(const void *a, const void *b) {
    struct Sentence *sent1 = (struct Sentence *) a;
    struct Sentence *sent2 = (struct Sentence *) b;
    wchar_t *last_word1 = sent1->words[sent1->words_count - 1];
    wchar_t *last_word2 = sent2->words[sent2->words_count - 1];
    if (sent1->words_count > 0 && sent2->words_count > 0) {
        return wcslen(last_word1) - wcslen(last_word2);
    } else if (sent1->words_count > 0){
        return wcslen(last_word1);
    } else if (sent2->words_count > 0){
        return -wcslen(last_word2);
    } else return 0;
}

