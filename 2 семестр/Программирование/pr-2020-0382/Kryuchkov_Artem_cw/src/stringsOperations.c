#include "stringsOperations.h"
struct Text deleteSentence(struct Text text, int indexToDelete) {

    free(text.sentences[indexToDelete]->words);
    free(text.sentences[indexToDelete]);
    for (int i = indexToDelete; i < text.n; i++) {
        if (i != indexToDelete) {
            text.sentences[i - 1] = text.sentences[i];
        }
    }
    text.n = text.n - 1;
    return text;
}

struct Text deleteRepeatedSentences(struct Text text) {
    int ntext = text.n;
    for (int i = 0; i < ntext; i++) {
        for (int j = i + 1; j < ntext; j++) {
            if ((wcscasecmp(text.sentences[i]->words, text.sentences[j]->words) == 0)) {
                text = deleteSentence(text, j);
                j--;
                ntext--;
            }
        }
    }
    text.n = ntext;
    return text;
}

struct Text deleteBigSentences(struct Text text) {
    struct Sentence *s;
    for (int i = 0; (int) i < text.n; ++i) {
        s = text.sentences[i];
        if (countWords(*s) > 10) {
            text = deleteSentence(text, i);
            i--;
        }
    }
    return text;
}

struct Text changeEnding(struct Text text) {
    struct Sentence *s;
    wchar_t *newword;
    int newsize;
    int newn;
    for (int i = 0; i < text.n; ++i) {
        s = text.sentences[i];
        newsize = s->size;
        newword = malloc(newsize * sizeof(wchar_t));
        newn = 0;
        for (int j = 0; j < (s->n + 3); ++j) {
            if (newn == newsize - 2) {
                newsize += INIT;
                newword = realloc(newword, newsize * sizeof(wchar_t));
            }
            if (j < (s->n - 2)) {
                if ((wcsncmp(L"тся", (*s).words + j, 3) == 0) && wcschr(L" .,\n", ((*s).words[j + 3])) != NULL) { //тся
                    newword[newn++] = s->words[j];
                    newword[newn++] = L'ь';
                } else if (j < s->n - 3) {//ться
                    if ((wcsncmp(L"ться", (*s).words + j, 4) == 0) &&
                        wcschr(L" .,\n", ((*s).words[j + 4])) != NULL) { //тся
                        newword[newn++] = s->words[j];
                        newword[newn++] = L'с';
                        newword[newn++] = L'я';
                        j += 3;
                    } else {
                        newword[newn++] = s->words[j];
                    }
                } else {
                    newword[newn++] = s->words[j];
                }
            } else {
                newword[newn++] = s->words[j];
            }
            if (s->words[j] == L'\0') {
                break;
            }
        }
        free(text.sentences[i]->words);
        text.sentences[i]->words = newword;
        text.sentences[i]->n = newn - 1;
        text.sentences[i]->size = newsize;
    }
    return text;
}


int countWords(struct Sentence s) {
    int res = 0;
    int k = 0;
    for (int i = 0; i < s.n - 1; ++i) {
        if ((s.words[i] == ' ' && k == 0) ||
            (s.words[i] == ',' && k == 0)) { // k необходимо для проверки на множественный ввод пробелов или запятых
            res++;
            k = 1;
        } else if (s.words[i] != ' ' && s.words[i] != ',' && s.words[i] != '\n') {
            k = 0;
        }
    }
    if (res > 0 || (res == 0 && s.n > 1)) res++;
    return res;
}

int compareSentencesByWords(const void *ss1, const void *ss2) {
    struct Sentence *s1 = *(struct Sentence **) ss1;
    struct Sentence *s2 = *(struct Sentence **) ss2;
    int ns1 = countWords(*s1);
    int ns2 = countWords(*s2);
    return ns1 - ns2;
}

