#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#include "structures.h"
#include "funcs_for_tasks.h"

#define INIT_SIZE 50

int is_palindrom(struct Sentence Sent){
    int i, j, count1;
    int count2 = 0;
    for (j=0; j<Sent.count_w; j++) {
        count1 = 1;
        for (i=0; i<(Sent.len_w[j]/2); i++){
            if (Sent.words[j][i] == Sent.words[j][(Sent.len_w[j]-1-i)]){
                count1 *= 1;
            }
            else{
                count1 *= 0;
            }
        }
        if (count1){
            count2 += 1;
        }
    }
    if (count2 == Sent.count_w){
        return 1;
    }
    if (count2 == 0){
        return 0;
    }
    if ((count2 < Sent.count_w) && (count2 != 0)){
        return 2;
    }
}


struct Sentence special_sym(struct Sentence Sent){
    int i,j;
    wchar_t* s = L">special symbol<";
    for (i=0; i< Sent.len_s;){
        if (Sent.len_s > Sent.size_sent - 16){
            Sent.size_sent += INIT_SIZE;
            Sent.sentence = realloc(Sent.sentence, Sent.size_sent * (sizeof(wchar_t)));
        }
        if ((iswalpha(Sent.sentence[i]) == 0) && (iswdigit(Sent.sentence[i]) == 0) && (Sent.sentence[i] != L'.')){
            for (j=Sent.len_s-1; j>i; j--){
                Sent.sentence[j+15] = Sent.sentence[j];
            }
            Sent.len_s += 15;
            Sent.sentence[Sent.len_s] = L'\0';
            for (j=0; j<wcslen(s); j++){
                Sent.sentence[i] = s[j];
                i++;
            }
        }
        else{
            if (Sent.sentence[i] == L'.'){
                Sent.len_s += 15;
                Sent.sentence[Sent.len_s] = L'\0';
                for (j=0; j<wcslen(s); j++){
                    Sent.sentence[i] = s[j];
                    i++;
                }
            }
            else{
                i++;
            }
        }
    }
    return Sent;
}


int delete_sent(struct Sentence Sent){
    int i,j, flag1, flag2;
    for (i = 0; i<Sent.count_w; i++){
        flag1 = 1;
        flag2 = 1;
        for (j = 0; j<Sent.len_w[i]; j++){
            if (((Sent.words[i][j] >= L'а') && (Sent.words[i][j] <= L'я')) || ((Sent.words[i][j] >= L'А') && (Sent.words[i][j] >= L'Я'))){
                flag1 = 0;
            }
            else {
                if (isalpha(Sent.words[i][j])) {
                    flag2 = 0;
                }
            }
        }
        if ((flag1 == 0) && (flag2 == 0)){
            return 1;
        }
    }
    return 0;
}
