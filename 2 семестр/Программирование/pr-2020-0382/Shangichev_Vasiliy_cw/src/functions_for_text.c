#include <stdio.h>
#include <wchar.h>
#include "consts.h"
#include <stdlib.h>
#include "functions_for_text.h"
#include <wctype.h>
#include "string_functions.h"

void free_memory(struct Text* text){
    int i, j;
    for (i = 0; i < text->text_len; i++){
        for (j = 0; j < text->sentences[i].words_number; j++){
            free(text->sentences[i].words[j].symbols);
        }
        free(text->sentences[i].words);
        free(text->sentences[i].separators);
    }
    free(text->sentences);
}

void get_words(struct Text* text) {
    int in_sentence = 1;
    wchar_t** p_for_sym_buf;
    wchar_t* p_for_sym;
    struct Word** p_for_st_words_b;
    struct Word* p_for_st;
    int max_stwords = MAXSTWORDS;
    int max_stlen = MAXSTLEN;
    int max_sy_words = MAXSYWORDS;
    int max_sy_len = MAXSYLEN;
    int max_sep_arlen = ARRAYBUF;
    int max_seps_num = ARRAYBUF;
    int struct_index = 0;
    int sentence_index = 0;
    int word_index = 0;
    int symbol_index = 0;
    int sep_index = 0;
    int i, j, k;
    wchar_t current_symbol;

    wchar_t** separators = malloc(sizeof(wchar_t*) * max_sep_arlen);
    for (i = 0; i < max_sep_arlen; i++){
        separators[i] = malloc(sizeof(wchar_t) * max_seps_num);
    }

    struct Word** st_words_buffer = malloc(sizeof(struct Word*) * max_stwords);
    for (i = 0; i < max_stwords; i++){
        st_words_buffer[i] = malloc(sizeof(struct Word) * max_stlen);
    }

    wchar_t** symbols_buffer = malloc(sizeof(wchar_t*) * max_sy_words);
    for (i = 0; i < max_sy_words; i++){
        symbols_buffer[i] = malloc(sizeof(wchar_t) * max_sy_len);
    }


    for (i = 0; i < text->text_len; i++){
        in_sentence = 1;
        for (j = 0;;j++){
            current_symbol = text->sentences[i].chars[j];
            symbols_buffer[word_index][symbol_index] = current_symbol;
            symbol_index += 1;

            if (symbol_index == max_sy_len){
                max_sy_len *= 2;
                for (k = word_index; k < max_sy_words; k++){
                    p_for_sym = realloc(symbols_buffer[k], sizeof(wchar_t) * max_sy_len);
                    if (p_for_sym){
                        symbols_buffer[k] = p_for_sym;
                    }
                }
            }
            if (current_symbol == L' ' || current_symbol == L','){
                // end of word
                separators[sentence_index][sep_index++] = current_symbol;
                symbols_buffer[word_index][symbol_index-1] = '\0';
                st_words_buffer[sentence_index][struct_index].symbols = symbols_buffer[word_index];
                struct_index += 1;
                word_index += 1;
                symbol_index = 0;
            }

            if (sep_index == max_seps_num){
                max_seps_num *= 2;
                for (k = sentence_index; k < max_sep_arlen; k++){
                    p_for_sym = realloc(separators[k], sizeof(wchar_t) * max_seps_num);
                    if (p_for_sym){
                        separators[k] = p_for_sym;
                    }
                }
            }

            if (current_symbol == L'.'){
                symbols_buffer[word_index][symbol_index-1] = '\0';
                st_words_buffer[sentence_index][struct_index].symbols = symbols_buffer[word_index];
                symbol_index = 0;
                word_index += 1;
                sentence_index += 1;
                if (sentence_index == max_stwords){
                    max_stwords *= 2;
                    p_for_st_words_b = realloc(st_words_buffer, sizeof(struct Word*) * max_stwords);
                    if (p_for_st_words_b){
                        st_words_buffer = p_for_st_words_b;
                    }
                    for (k = sentence_index; k < max_stwords; k++){
                        st_words_buffer[k] = malloc(sizeof(struct Word) * max_stlen);
                    }
                    
                }
                text->sentences[i].words = st_words_buffer[sentence_index-1];
                text->sentences[i].words_number = struct_index + 1;
                text->sentences[i].separators = separators[sentence_index-1];
                sep_index = 0;
                struct_index = 0;
                in_sentence = 0;
            }

            if (sentence_index == max_sep_arlen){
                max_sep_arlen *= 2;
                p_for_sym_buf = realloc(separators, sizeof(wchar_t*) * max_sep_arlen);
                if (p_for_sym_buf){
                    separators = p_for_sym_buf;
                }
                for (k = sentence_index; k < max_sep_arlen; k++){
                    p_for_sym = realloc(separators[k], sizeof(wchar_t) * max_seps_num);
                    if (p_for_sym){
                        separators[k] = p_for_sym;
                    }
                }
            }

            if (struct_index == max_stlen){
                max_stlen *= 2;
                for (k = sentence_index; k < max_stwords; k++){
                    p_for_st = realloc(st_words_buffer[k], sizeof(struct Word) * max_stlen);
                    if (p_for_st){
                        st_words_buffer[k] = p_for_st;
                    }
                }
            }
            if (word_index == max_sy_words){
                max_sy_words *= 2;
                p_for_sym_buf = realloc(symbols_buffer, sizeof(wchar_t*) * max_sy_words);
                if (p_for_sym_buf){
                    symbols_buffer = p_for_sym_buf;
                }
                for (k = word_index; k < max_sy_words; k++){
                    symbols_buffer[k] = malloc(sizeof(wchar_t) * max_sy_len);
                }
            }
            if (!in_sentence){
                break;
            }
        }
    }

    for (k = sentence_index; k < max_sep_arlen; k++){
        free(separators[k]);
    }

    for (k = word_index; k < max_sy_words; k++){
       free(symbols_buffer[k]);
    }
    for (k = sentence_index; k < max_stwords; k++){
        free(st_words_buffer[k]);
    }
    for (k = 0; k < text->text_len; k++){
        free(text->sentences[k].chars);
    }
    free(separators);
    free(symbols_buffer);
    free(st_words_buffer);

}

void get_text(struct Text* processed_text){
    int is_enter = 0;
    int is_equal = 1;
    wchar_t** p_for_text;
    wchar_t* p_for_sentence;
    int i, j;
    wchar_t current_symbol;
    int current_symbol_index = 0;
    int current_sentence_index = 0;
    int current_max_text_len = TEXTSIZE;
    int current_max_sentence_len = BUFSIZE;

    wchar_t** text = (wchar_t**)malloc(sizeof(wchar_t*) * current_max_text_len);

    for (i = 0; i < current_max_text_len; i++){
        text[i] = (wchar_t*)malloc(sizeof(wchar_t) * current_max_sentence_len);
    }

    // reading text
    while ((current_symbol = getwchar()) != L'\n' || is_enter == 0){
        if (current_symbol == L'\n'){
            is_enter = 1;
            continue;
        }
        is_enter = 0;
        text[current_sentence_index][current_symbol_index] = current_symbol;
        current_symbol_index += 1;

        if (current_symbol_index == current_max_sentence_len){
            // add memory
            current_max_sentence_len *= 2;
            for (i = current_sentence_index; i < current_max_text_len; i++){
                p_for_sentence = (wchar_t*)realloc(text[i], sizeof(wchar_t) * current_max_sentence_len);
                if (p_for_sentence){
                    text[i] = p_for_sentence;
                }
            }
        }
        if (current_symbol == '.'){
            // end of sentence
            text[current_sentence_index][current_symbol_index] = '\0';
            // check string
            for (i = 0; i < current_sentence_index; i++){
                is_equal = wcscasecmp(text[i], text[current_sentence_index]);
                if (!is_equal){
                    // не добавлять строку
                    for (j = 0; j <= current_symbol_index; j++){
                        text[current_sentence_index][j] = 0;
                    }
                    break;
                }
            }
            current_symbol_index = 0;
            if (is_equal){
                current_sentence_index += 1;
            }
        }

        if (current_sentence_index == current_max_text_len){
            // add memory
            current_max_text_len *= 2;
            p_for_text = (wchar_t**)realloc(text, sizeof(wchar_t*) * current_max_text_len);
            if (p_for_text){
                text = p_for_text;
            } 
            for (i = current_sentence_index; i < current_max_text_len; i++){
                text[i] = (wchar_t*)malloc(sizeof(wchar_t) * current_max_sentence_len);
            }
        }
    }

    // free memory
    for (i = current_sentence_index; i < current_max_text_len; i++){
        free(text[i]);
    }

    struct Sentence* sentences = malloc(sizeof(struct Sentence) * current_sentence_index);

    // init structures
    for (i = 0; i < current_sentence_index; i++){
        sentences[i].chars = text[i];
    }
    free(text);
    processed_text->sentences = sentences;
    processed_text->text_len = current_sentence_index;
}


void print_text(struct Text* text){
    int i, j, k;
    for (i = 0; i < text->text_len; i++){
        k = 0;

        for (j = 0; j < text->sentences[i].words_number; j++){
            wprintf(L"%ls", text->sentences[i].words[j]);
            if (k != text->sentences[i].words_number - 1){
                wprintf(L"%lc", text->sentences[i].separators[k++]);
            }
        }
        wprintf(L".\n");
    }
}

void replace_digits(struct Text* text){
    int is_digit;
    int max_digit_for_replace_len = 0;
    int index;
    int array[10];
    wchar_t current_char;
    int i, j, k, w;
    for (i = 0; i < 10; i++){
        array[i] = 0;
    }
    int num_digits = 0;
    int max_wb_len = ARRAYBUF;
    int max_b_len = ARRAYBUF;
    wchar_t** wb_p;
    wchar_t* b_p;
    int wb_index = 0;
    int b_index = 0;
    int str_len;
    wchar_t current_symbol;
    wchar_t** words_buffer = malloc(sizeof(wchar_t*) * max_wb_len);
    for (i = 0; i < max_wb_len; i++){
        words_buffer[i] = malloc(sizeof(wchar_t) * max_b_len);
    }

    for (i = 0; i < text->text_len; i++){
        for (j = 0; j < text->sentences[i].words_number; j++){
            k = 0;
            while (text->sentences[i].words[j].symbols[k] != '\0'){
                is_digit = iswdigit(text->sentences[i].words[j].symbols[k]);
                if (is_digit){
                    num_digits++;
                    index = text->sentences[i].words[j].symbols[k] - L'0';
                    array[index]++;
                }
                k++;
            }
        }
    }
    while (num_digits > 0){
        max_digit_for_replace_len++;
        num_digits /= 10;
    }

    wchar_t** strings_for_replace = malloc(sizeof(wchar_t*) * 10);
    for (i = 0; i < 10; i++){
        strings_for_replace[i] = malloc(sizeof(wchar_t) * (max_digit_for_replace_len + 1));
    }
    for (i = 0; i < 10; i++){
        swprintf(strings_for_replace[i], max_digit_for_replace_len + 1, L"%d", array[i]);
    }

    for (i = 0; i < text->text_len; i++){
        for (j = 0; j < text->sentences[i].words_number; j++){
            k = 0;
            while (text->sentences[i].words[j].symbols[k] != '\0'){
                current_symbol = text->sentences[i].words[j].symbols[k];
                words_buffer[wb_index][b_index] = current_symbol;
                is_digit = iswdigit(current_symbol);
                k++;
                if (is_digit){
                    words_buffer[wb_index][b_index] = '\0';
                    str_len = wcslen(strings_for_replace[current_symbol - L'0']);
                    while (max_b_len - b_index - 1 < str_len){
                        max_b_len *= 2;
                        for (w = wb_index; w < max_wb_len; w++){
                            b_p = realloc(words_buffer[w], sizeof(wchar_t) * max_b_len);
                            if (b_p){
                                words_buffer[w] = b_p;
                            }
                        }
                    }
                    wcscat(words_buffer[wb_index], strings_for_replace[current_symbol - L'0']);
                    b_index += str_len - 1;
                }

                b_index++;
                if (b_index == max_b_len){
                    max_b_len *= 2;
                    for (w = wb_index; w < max_wb_len; w++){
                        b_p = realloc(words_buffer[w], sizeof(wchar_t) * max_b_len);
                        if (b_p){
                            words_buffer[w] = b_p;
                        }
                    }
                }

            }
            free(text->sentences[i].words[j].symbols);
            words_buffer[wb_index][b_index] = '\0';
            text->sentences[i].words[j].symbols = words_buffer[wb_index++];
            b_index = 0;
            if (wb_index == max_wb_len){
                max_wb_len *= 2;
                wb_p = realloc(words_buffer, sizeof(wchar_t*) * max_wb_len);
                if (wb_p){
                    words_buffer = wb_p;
                }
                for (w = wb_index; w < max_wb_len; w++){
                    words_buffer[w] = malloc(sizeof(wchar_t) * max_b_len);
                }
            }


        }
    }

    for (i = wb_index; i < max_wb_len; i++){
        free(words_buffer[i]);
    }
    for (i = 0; i < 10; i++){
        free(strings_for_replace[i]);
    }
    free(strings_for_replace);
    free(words_buffer);
}

void sort_words(struct Text* text){
    int i;

    for (i = 0; i < text->text_len; i++){
        qsort(text->sentences[i].words, text->sentences[i].words_number, sizeof(struct Word), compare_words);
    }
}
