#include <wchar.h>
#include "string_functions.h"
#include "consts.h"
#include <stdlib.h>
#include <wctype.h>
#include "functions_for_sentence.h"
#include <stdio.h>

void get_substrings(struct Substrings* substrings, struct Text* text){
    // create two arrays:
    // words and num occuriences
    wchar_t* current_word;
    int next_max_word_len;
    struct Sentence current_sentence;
    int i, j, k, w, difference, word_len;
    int* p_for_occuriences;
    wchar_t** p_for_warray;
    wchar_t* p_for_word;
    int is_equal;
    int num_words = 0;
    int max_array_len = ARRAYBUF;
    int max_words_array_len = MAXSYWORDS;
    int max_word_len = MAXSYLEN;
    int* occuriences = calloc(max_array_len, sizeof(int));
    wchar_t** words = malloc(sizeof(wchar_t*) * max_words_array_len);
    for (i = 0; i < max_words_array_len; i++){
        words[i] = malloc(sizeof(wchar_t) * max_word_len);
    }
    for (i = 0; i < text->text_len; i++){ 
        current_sentence = text->sentences[i];
        for (j = 0; j < current_sentence.words_number; j++){
            current_word = current_sentence.words[j].symbols;
            for (k = 0; k < num_words; k++){
                is_equal = wcscmp(current_word, words[k]);
                if (!is_equal){
                    occuriences[k]++;
                    break;
                }
            }
            if (k == num_words){
                // create new word
                // check memory
                // for occuriences
                if (k == max_array_len){
                    // add memory
                    max_array_len *= 2;
                    p_for_occuriences = realloc(occuriences, sizeof(int) * max_array_len);
                    if (p_for_occuriences){
                        occuriences = p_for_occuriences;
                    }
                    for (w = k; w < max_array_len; w++){
                        occuriences[w] = 0;
                    }
                }
                // for words array
                if (k == max_words_array_len){
                    max_words_array_len *= 2;
                    p_for_warray = realloc(words, sizeof(wchar_t*) * max_words_array_len);
                    if (p_for_warray){
                        words = p_for_warray;
                    }
                    for (w = num_words; w < max_words_array_len; w++){
                        p_for_word = malloc(sizeof(wchar_t) * max_word_len);
                        if (p_for_word){
                            words[w] = p_for_word;
                        }
                    }

                }
                // check word len
                word_len = wcslen(current_word);
                if (word_len + 1 > max_word_len){
                    // решаем сколько памяти надо выделить
                    difference = word_len + 1 - max_word_len;
                    if (difference > max_word_len){
                        next_max_word_len = difference + max_word_len;
                    } else {
                        next_max_word_len = max_word_len * 2;
                    }
                    max_word_len = next_max_word_len;
                    for (w = num_words; w < max_words_array_len; w++){
                        p_for_word = realloc(words[w], sizeof(wchar_t) * max_word_len);
                        if (p_for_word){
                            words[w] = p_for_word;
                        }
                    }
                }
                // write new word
                wcscpy(words[num_words], current_word);
                occuriences[num_words]++;
                num_words++;
            }
        }
    }
    // free memory
    for (i = num_words; i < max_words_array_len; i++){
        free(words[i]);
    }

    substrings->words = words;
    substrings->num_occur = occuriences;
    substrings->num_words = num_words;
}


int get_number_of_latin_letters(struct Word word){
    int i = 0;
    int number = 0;
    while (word.symbols[i] != L'\0'){
        if ((word.symbols[i] >= L'A' && word.symbols[i] <= L'Z') || (word.symbols[i] >= L'a' && word.symbols[i] <= L'z')){
            number += 1;
        }
        i += 1;
    }
    return number;
}

int compare_words(const void* a, const void* b){
    struct Word* word_1 = (struct Word*)a;
    struct Word* word_2 = (struct Word*)b;

    if (word_1->number_of_latin_letters < word_2->number_of_latin_letters){
        return 1;
    }
    if (word_1->number_of_latin_letters > word_2->number_of_latin_letters){
        return -1;
    }
    return 0;
}


void set_k(struct Text* text){
    int i;
    for (i = 0; i < text->text_len; i++){
        if (check_kirl(&(text->sentences[i]))){
            reverse(&(text->sentences[i]));
        }
 
    }
}

