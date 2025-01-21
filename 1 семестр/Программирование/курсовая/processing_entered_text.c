#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

#define MEM_STEP 15

struct Sentence{
    wchar_t* str;
    int len; 
    int size;
    int words;
};

struct Text{
    struct Sentence** sent;
    int size;
    int cnt_sent;
};

struct Sentence* readSentence(){
    int size = MEM_STEP;
    wchar_t* buf = malloc(size * sizeof(wchar_t));
    wchar_t temp;
    int ind_symb = 0;
    int words = 0;
    do{
        if (ind_symb <= size-2){
            wchar_t* t = realloc(buf, size + MEM_STEP);
            if(!t){
                wprintf(L"Ошибка!Закончилась память.");
            }
            size += MEM_STEP;
            buf = t;
        }
        temp = getwchar();
        buf[ind_symb] = temp;
        if (iswpunct(buf[ind_symb]) || iswspace(buf[ind_symb]))
            words++;
        ind_symb++;
    }while(temp != '.' && temp != '\n');
    buf[ind_symb] = '\0';
    struct Sentence* sentence= malloc(sizeof(struct Sentence));
    sentence -> str = buf;
    sentence -> size = size;
    sentence -> len = ind_symb - 1;
    sentence -> words = words;
    return sentence;
}

struct Text readText(){
    int size = MEM_STEP;
    struct Sentence** text = malloc(size*sizeof(struct Sentence));
    int ind_sent = 0;
    struct Sentence* temp;
    int null = 0;
    do{
        temp = readSentence();
        if(temp -> str[0] == '\n'){
            null++;
            free(temp -> str);
            free(temp);
        }
        else{
            null=0;
            text[ind_sent] = temp;
            ind_sent++;
        }
    }while (null < 1);
    struct Text enter_text;
    enter_text.size = size;
    enter_text.sent = text;
    enter_text.cnt_sent = ind_sent;
    return enter_text;
}

struct Text del_repeat_sent(struct Text text)
{
    wchar_t* words;
    wchar_t* words_compare;
    struct Text right_text = text;
    int text_len = right_text.cnt_sent;
    for(int i = 0; i < text_len; i++){
        words = right_text.sent[i] -> str;
        int words_len = right_text.sent[i] -> len;
        for(int j = i + 1; j < text_len; j++){
            words_compare = right_text.sent[j] -> str;
            int compare_len = right_text.sent[j] -> len;
            int same_symb = 0;
            if(words_len == compare_len) {
                for (int k = 0; k < right_text.sent[j] -> len; k++) {
                    if (towupper(words[k]) == towupper(words_compare[k]))
                        same_symb = 1;
                    else{
                        same_symb = 0;
                        break;
                    }
                }
            }
            if(same_symb){
                free(right_text.sent[text_len]);
                memmove(&right_text.sent[j], &right_text.sent[j+1], (text_len-j)*sizeof(struct Sentence*));
                text_len--;
                j--;
            }
        }
    }
    right_text.cnt_sent = text_len;
    return right_text;
}

void print_text(struct Text* text){
	for (int i = 0; i < text -> cnt_sent; i++)
		wprintf(L"%ls", text -> sent[i] -> str);
}

void free_text(struct Text* text){
	for(int i = 0; i < text -> cnt_sent; i++)
		free(text -> sent[i]);
}

