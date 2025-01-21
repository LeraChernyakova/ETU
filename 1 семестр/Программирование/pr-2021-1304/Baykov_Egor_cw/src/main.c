#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <string.h>
#include "structures.h"
#include "addLetters.h"
#include "findAnagram.h"
#include "sortSentences.h"
#include "replace.h"
#define MEM_STEP 20

wchar_t delSpace(){
    wchar_t c = getwchar();
    while(c == L' '){
        c = getwchar();
    }
    return c;
}

struct Sentence* readSentence(){
    int size = MEM_STEP;
    wchar_t* t = malloc(size*sizeof(wchar_t));
    wchar_t* buf;
    if(t != NULL){
        buf = t;
    }
    else{
        wprintf(L"Error. readSentence.");
        return NULL;
    }
    int n = 0;
    wchar_t temp;
    do{
        if(n >= size - 2){
            size += MEM_STEP;
            t = realloc(buf, size*sizeof(wchar_t));
            if(t != NULL){
                buf = t;
            }
            else{
                free(buf);
                return NULL;
            }
        }
        if(n == 0){
            temp = delSpace();
        }
        else{
            temp = getwchar();
        }
        buf[n++] = temp;
        if(buf[0] == L'\n' && buf[1] == L'\n'){
            break;
        }
    } while(temp != L'.');
    buf[n] = L'\0';
    t = realloc(buf, sizeof(wchar_t) * (n + 1));
    if(t != NULL){
        buf = t;
    }
    else{
        wprintf(L"Error. readSentence.");
        return NULL;
    }
    struct Sentence* t_sent = malloc(sizeof(struct Sentence));
    struct Sentence* sentence;
    if(t_sent != NULL){
        sentence = t_sent;
    }
    else{
        free(buf);
        wprintf(L"Error. Structure fail");
        return NULL;
    }

    sentence -> string = buf;
    sentence -> size = size;
    sentence -> len = n + 1; // With /0
    return sentence;
}

struct Text readText(){
    int size = MEM_STEP;
    struct Sentence** t = malloc(size * sizeof(struct Sentence*));
    struct Text text;
    struct Sentence** sentence;
    if (t != NULL){
        sentence = t;
    }
    else{
        text.len = 0;
        return text;
    }
    int n = 0;
    struct Sentence* temp;
    do{
        temp = readSentence();

        if(n == size){
            size += MEM_STEP;
            t = realloc(sentence, size * sizeof(struct Sentence*));
            if (t != NULL){
                sentence = t;
            }
            else{
                for(int i = 0; i < text.len; i++){
                    free(text.sentences[i] -> string);
                }
                free(text.sentences);
                text.len = 0;
                return text;
            }
        }

        if(temp != NULL){
            sentence[n++] = temp;
        }
        else{
            for(int i = 0; i < text.len; i++){
                    free(text.sentences[i] -> string);
                    free(text.sentences[i]);
                }
                free(text.sentences);
                text.len = 0;
                return text;
        }
    } while(wcscmp(sentence[n-1] -> string, L"\n\n"));

    text.size = size;
    text.sentences = sentence;
    text.len = n;

    return text;
}

void printText(struct Text text){
    for(int i = 0; i < text.len - 1; i++){
        wprintf(L"%ls ", text.sentences[i] -> string);
    }
    wprintf(L"\n");
}

void freeText(struct Text text){
    for(int i = 0; i < text.len; i++){
        free(text.sentences[i] -> string);
        free(text.sentences[i]);
    }
    free(text.sentences);
}

int deleteSentence(struct Text text){
    struct Sentence** sen = text.sentences;
    int new_len = text.len;
    int i = 1;
    int flag = 0;
    while(sen < text.sentences + new_len - 1){
        while(sen + i < text.sentences + new_len){
            if(!wcscasecmp((*sen) -> string, (*(sen + i)) -> string)){
                free((*(sen + i)) -> string);
                free((*(sen + i)));
                new_len--;
                memmove(sen + i, sen + i + 1, sizeof(struct Sentence*) * (text.sentences + new_len - sen - i));
                flag = 1;
            }
            else{
                i++;
            }
        }
        if(flag){
            flag = 0;
            i = 1;
            free((*sen) -> string);
            free((*sen));
            new_len--;
            memmove(sen, sen + 1, sizeof(struct Sentence*) * (text.sentences + new_len - sen));
        }
        else{
            i = 1;
            sen++;
        }
    }
    return new_len;
}

int main(){
    setlocale(LC_ALL, "");
    wprintf(L"Введите текст, который хотите обработать\n");
    struct Text text = readText();
    wchar_t* word;
    text.len = deleteSentence(text);
    int command = 0;
    while(command != 5){
        wprintf(L"Введите команду\n(1) - Поиск анаграм\n(2) - Сортировка предложений по заглавным буквам\n(3) - Замена гласных букв\n(4) - Замена слова\n(5) - выход\n");
        wscanf(L"%d", &command);
        switch (command)
        {
            case 1:
                findAnagram(text);
                break;
            case 2:
                sortSentences(text);
                printText(text);
                break;
            case 3:
                addLetters(text);
                printText(text);
                break;
            case 4:
                getwchar();
                replace(text);
                printText(text);
                break;
            case 5:
                wprintf(L"Завершение работы программы\n");
                break;
            default:
                wprintf(L"Неверная команда\n");
                break;
        }
    }
    printText(text);
    freeText(text);
    return 0;
}