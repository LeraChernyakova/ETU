#include "functions.h"

void print(TEXT * work_text){
    int i = 0;
    if (work_text->text[i].sent[0].word[0] != L'\n') {
        do {
            for (int j = 0; j < work_text->text[i].len; j++) {
                wchar_t *arr = work_text->text[i].sent[j].word;
                wprintf(L"%ls", arr);
            }
            i++;
            wprintf(L".");
        } while (work_text->text[i].sent[0].word[0] != L'\n');
    }
    wprintf(L"\n");
}

void print_word(TEXT * work_text){
    for (int i = 0; i < work_text->len-1; ++i) {
        for (int j = 0; j < work_text->text[i].len; ++j) {
            int flag = 0;
            if ((work_text->text[i].sent[j].word[0] != L' ') && (work_text->text[i].sent[j].word[0] != L',')) {
                for (int k = 0; k < work_text->len - 1; ++k) {
                    for (int l = 0; l < work_text->text[k].len; ++l) {
                        if (!(wcscasecmp(work_text->text[i].sent[j].word, work_text->text[k].sent[l].word))){
                            flag++;
                        }
                    }
                }
                if (flag == 1){
                    wprintf(L"%ls ", work_text->text[i].sent[j].word);
                }
            }
        }
    }
    wprintf(L"\n");
}

void fix_data(TEXT * work_text){
    wchar_t month[12][30] = {L"Января", L"Февраля", L"Марта", L"апреля", L"Мая", L"Июня", L"Июля", L"Августа", L"Сентября", L"Октября", L"Ноября", L"Декабря"};
    for (int i = 0; i < work_text->len-1; ++i) {
        for (int j = 0; j < work_text->text[i].len - 6; ++j) {
            if (work_text->text[i].sent[j].len == 3 && isDigit(work_text->text[i].sent[j].word[0]) && isDigit(work_text->text[i].sent[j].word[1])){
                if (work_text->text[i].sent[j+4].len == 5 && isDigit(work_text->text[i].sent[j+4].word[0]) && isDigit(work_text->text[i].sent[j+4].word[1]) && isDigit(work_text->text[i].sent[j+4].word[2]) && isDigit(work_text->text[i].sent[j+4].word[3])){
                    if (work_text->text[i].sent[j+6].word[0] == L'г'){
                        int nam;
                        for (nam = 0; nam < 12; ++nam) {
                            if (!wcscasecmp(month[nam], work_text->text[i].sent[j+2].word)) {
                                work_text->text[i].sent[j + 1].word = L"/\0";
                                work_text->text[i].sent[j + 3].word = L"/\0";
                                work_text->text[i].sent[j + 5].word = L"\0";
                                if (nam<9) {
                                    work_text->text[i].sent[j + 2].word[0] = '0';
                                    work_text->text[i].sent[j + 2].word[1] = (nam+1) +'0';
                                    work_text->text[i].sent[j + 2].word[2] = '\0';
                                }
                                else {
                                    work_text->text[i].sent[j + 2].word[0] = L'1';
                                    work_text->text[i].sent[j + 2].word[1] = ((nam+1)%10) +'0';
                                    work_text->text[i].sent[j + 2].word[2] = '\0';
                                }
                                free(work_text->text[i].sent[j+6].word);
                                free(work_text->text[i].sent[j+7].word);
                                work_text->text[i].len = work_text->text[i].len - 2;
                            }
                        }
                    }
                }
            }
        }
    }
}

void del_spe(TEXT * work_text){
    for (int i = 0; i < work_text->len;) {
        //wprintf(L"%d %d\n", work_text->text[i].spe, work_text->text[i].in);
        if ((work_text->text[i].spe != 0) && (work_text->text[i].in == 0)){
            shift(work_text, i);
        }
        else i++;
    }
}

void text_sort(TEXT * work_text){
    for (int i = 0; i < work_text->len-1; ++i) {
        long long int minmass, index;
        index = i;
        minmass = work_text->text[i].mass;
        //wprintf(L"%d\n", minmass);
        for (int j = i+1; j < work_text->len-1; ++j) {
            if (minmass > work_text->text[j].mass){
                index = j;
                minmass = work_text->text[j].mass;
            }
        }
        SENT help;
        help = work_text->text[i];
        work_text->text[i] = work_text->text[index];
        work_text->text[index] = help;
    }
}
