#include "output_funcs.h"

void put_printed_sent(struct Sentence sent) {
    if (sent.words_count) {
        int i, j;
        for (i = 0, j = 0; j < sent.words_count; i++) {
            while (wcschr(L" ,\t\n", sent.sentence[i])) {
                wprintf(L"%lc", sent.sentence[i++]); //
            }
            switch (wcslen(sent.words[j]) % 3) {
                case 0:
                    wprintf(RED L"%ls" RESET_C, sent.words[j]);
                    break;
                case 1:
                    wprintf(BLUE L"%ls" RESET_C, sent.words[j]);
                    break;
                case 2:
                    wprintf(GREEN L"%ls" RESET_C, sent.words[j]);
                    break;
                case 3:
                    wprintf(YELLOW L"%ls" RESET_C, sent.words[j]);
                    break;
            }
            i += (int) wcslen(sent.words[j++]) - 1;
        }
        for (; i < sent.sent_len; i++) {
            wprintf(L"%lc", sent.sentence[i]);
        }
    } else wprintf(L"%ls", sent.sentence);
}

int put_start_end_upper_words(struct Sentence sent) {
    int sign = 0;
    for (int i = 0; i < sent.words_count; i++) {
        wchar_t *word = sent.words[i];
        if (iswupper(word[0]) && iswupper(word[wcslen(word) - 1])) {
            wprintf(L" %ls ", word);
            sign = 1;
        }
    }
    return sign;
}

void put_sent_without_numbers(struct Sentence sent) {
    if (sent.words_count > 0) {
        int i, j;
        for (i = 0, j = 0; j < sent.words_count; i++) {
            while (wcschr(L" ,\t\n", sent.sentence[i])) {
                wprintf(L"%lc", sent.sentence[i++]); //
            }
            wchar_t *sign;
            wcstoll(sent.words[j], &sign, 10);
            if (*sign) {
                wprintf(L"%ls", sent.words[j]);
            }
            i += (int) wcslen(sent.words[j++]) - 1;
        }
        for (; i < sent.sent_len; i++) {
            wprintf(L"%lc", sent.sentence[i]);
        }
    } else wprintf(L"%ls", sent.sentence);
}


