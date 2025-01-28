#include "output.h"

void printText(struct Text text) {
    struct Sentence *s;
    struct Sentence **sen = text.sentences;
    for (unsigned int i = 0; i < text.n; i++) {
        s = sen[i];
        wprintf(L"%ls\n", s->words);
    }
}

void printSentsWithSecondWordFirstSent(struct Text text) {
    if (text.n == 0) return;
    struct Sentence *firstSent = text.sentences[0];
    if (firstSent->n == 1) return;
    int size = INIT;
    int n = 0, i = 0;
    wchar_t *word = malloc(size * sizeof(wchar_t));
    wchar_t wc;
    int found = 0;
    while (1) {
        wc = firstSent->words[n];
        n++;
        if (wcschr(L".", wc) && n != 0) {
            break;
        }
        if ((wcschr(L" .,", wc) && n != 0)) {
            if (found)break;
            found = 1;
            continue;
        }
        if (found) {
            word[i++] = wc;
            if (i == size - 2) {
                size += INIT;
                word = realloc(word, size * sizeof(wchar_t));
            }
        }
    };
    word[i] = L'\0';
    struct Sentence *s;
    int isIntSentOk;
    if (i == 0) return; // если только одно слово в первом предложении
    for (int j = 0; j < text.n; ++j) {
        s = text.sentences[j];
        isIntSentOk = wcsstr(s->words, word) != NULL;
        if (isIntSentOk) {
            for (int k = 0; k < s->n; ++k) {
                if (wcsncmp(word, (*s).words + k, i) == 0 &&
                    (wcschr(L" .,", *((*s).words + k + i)) != 0) &&
                    (k == 0 || (wcschr(L" .,", *((*s).words + k - 1)) != 0))) {
                    wprintf(L"\033[32m\%ls\033[0m", word);
                    k += i - 1;
                } else {
                    wc = *((*s).words + k);
                    wprintf(L"%lc", wc);
                }
            }
            wprintf(L"\n");
        }
    }
    free(word);
}