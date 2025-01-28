#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "structures.h"
#include "input_text.h"

#define INIT_SIZE 50

struct Sentence read_sentence() {
    struct Sentence Sent;
    Sent.size_sent = INIT_SIZE;
    Sent.len_s = 0;
    Sent.final = 0;
    Sent.count_w = 0;
    int i;
    int j=0;
    int k=0;

    Sent.sentence = malloc(Sent.size_sent * sizeof(wchar_t));

    wchar_t sym;
    sym = (wchar_t) fgetwc(stdin);
    if (sym == L'\n') {
        Sent.final = 1;
    }
    else {
        while (sym == L' ') {
            sym = (wchar_t) fgetwc(stdin);
        }
        Sent.sentence[Sent.len_s++] = sym;
        Sent.count_w = 1;
        do {
            sym = (wchar_t) fgetwc(stdin);
            if ((sym == L' ') || (sym == L',')){
                Sent.count_w += 1;
            }
            Sent.sentence[Sent.len_s++] = sym;
            if (Sent.len_s == Sent.size_sent - 2) {
                Sent.size_sent += INIT_SIZE;
                Sent.sentence = realloc(Sent.sentence, Sent.size_sent * (sizeof(wchar_t)));
            }
        } while (sym != L'.');
    }
    if (Sent.len_s > 0) {
        Sent.sentence[Sent.len_s] = L'\0';
    }

    Sent.words = malloc(Sent.size_sent * sizeof(wchar_t*));
    Sent.len_w = malloc(Sent.count_w * sizeof(int));
    for (i = 0; i<Sent.count_w; i++){
        Sent.words[i] = malloc(Sent.size_sent * sizeof(wchar_t));
    }

    for (i = 0; i<(Sent.len_s-1); i++){
        if ((Sent.sentence[i] == L' ') || (Sent.sentence[i] == L',')){
            Sent.words[k][j] = L'\0';
            Sent.len_w[k] = j;
            k += 1;
            j = 0;
        }
        else{
            Sent.words[k][j++] = Sent.sentence[i];
        }
        Sent.words[k][j] = L'\0';
        Sent.len_w[k] = j;
    }

    return Sent;
}

struct Text read_text(){
    int i, j;
    int not_same = 0;
    struct Text text;
    text.len_t = 0;
    text.size_text = INIT_SIZE;

    text.sentences = malloc(text.size_text * (sizeof(struct Sentence*)));
    while(1){
        struct Sentence Sent = read_sentence();

        for (i = 0; i<text.len_t; i++) {
            if (wcscasecmp(text.sentences[i].sentence, Sent.sentence)) {
                not_same += 1;
            }
        }
        if (Sent.final) {
            break;
        }
        if (not_same == text.len_t) {
            text.sentences[text.len_t++] = Sent;
            if (text.len_t == text.size_text - 2) {
                text.size_text += INIT_SIZE;
                text.sentences = realloc(text.sentences, text.size_text * (sizeof(struct Sentence *)));
            }
        }
        not_same = 0;
    }
    return text;
}
