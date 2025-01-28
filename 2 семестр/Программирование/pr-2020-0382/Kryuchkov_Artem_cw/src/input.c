#include "input.h"
struct Sentence *readSentence() {
    int size = INIT;
    int n = 0;
    wchar_t *words = malloc(size * sizeof(wchar_t));
    wchar_t wc;
    do {
        wc = fgetwc(stdin);
        if (wcschr(L" ", wc) && n == 0) {
            continue;
        }

        words[n] = wc;
        n++;
        if (n == size - 2) {
            size += INIT;
            words = realloc(words, size * sizeof(wchar_t));
        }
        if (wcschr(L"\n", wc) && n != 0) {
            break;
        }
    } while (!wcschr(L".\n", wc));
    words[n] = L'\0';
    struct Sentence *sentence = malloc(size * sizeof(struct Sentence));
    sentence->words = words;
    sentence->size = size;
    sentence->n = n;
    return sentence;
}

struct Text readText() {
    int size = INIT;
    int n = 0;
    struct Sentence **sentences = malloc(size * sizeof(struct Sentence *));
    struct Sentence *sentence;
    while (1) {
        sentence = readSentence();
        if (sentence->words[sentence->n - 1] == L'\n') {
            if (sentence->n == 1) {
                free(sentence->words);
                free(sentence);
            } else {
                sentence->words[sentence->n-1]=L'\0';
                sentences[n] = sentence;
                n++;
            }
            break;
        } else {
            sentences[n] = sentence;
            n++;
            if (n == size - 2) {
                size += INIT;
                sentences = realloc(sentences, size * sizeof(struct Sentence *));
            }
        }
    }
    struct Text text;
    text.sentences = sentences;
    text.size = size;
    text.n = n;
    return text;
}


