#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_STEP 20
#define END_SENTENCE "Dragon flew away!\n"

char delTabs(){
    char c = getchar();
    for(c; c == ' ' || c == '\n' || c == '\t'; c = getchar()){}
    return c;
}

char* readSentence(){
    int size = MEMORY_STEP;
    char* t = malloc(size * sizeof(char));
    char temp;
    
    if(t != NULL){
        int ind_ch = 0;
        char* sentence = t;
        sentence[ind_ch++] = delTabs();
            do{
                if (ind_ch >= size - 2){
                    size += MEMORY_STEP;
                    t = realloc(sentence, size * sizeof(char));
                    if(t != NULL){
                        sentence = t;
                    }
                    else{
                        free(sentence);
                        return NULL;
                    }
                }
                temp = getchar();
                sentence[ind_ch++] = temp;
            } while(sentence[ind_ch-1] != '.' && sentence[ind_ch-1] != ';' && sentence[ind_ch-1] != '?' && sentence[ind_ch-1] != '!');
        sentence[ind_ch++] = '\n';
        sentence[ind_ch] = '\0';
        return sentence;
    }
    else{
        return NULL;
    }
}

int readText(char*** text, char* end_sentence){
    int size = MEMORY_STEP;
    char** t = malloc(size * sizeof(char*));
    
    if (t != NULL){

        (*text) = t;
        int i = 0;
        char* sentence;
        
        do{
            if(i == size){
                size += MEMORY_STEP;
                t = realloc((*text), size * sizeof(char*));
                if (t != NULL){
                    (*text) = t;
                }
                else{
                    for(int j = 0; j < i; j++){
                        free((*text)[j]);
                    }
                    free(*text);
                    return 0;
                }
            }
            sentence = readSentence();
            if(sentence != NULL){
                (*text)[i++] = sentence;
            }
            else{
                for(int j = 0; j < i; j++){
                    free((*text)[j]);
                }
                free(*text);
                return 0;
            }
        } while(strcmp(sentence, end_sentence));

        return i;
    }
    else{
        return 0;
    }
}

int deleteSentence(char** text, int len){
    char** sentence = text;
    while(sentence < text + len){
        if(strchr(*sentence, '?')){
            free(*sentence);
            len--;
            memmove(sentence, sentence + 1, sizeof(char*) * (text + len - sentence));
        }
        else{
            sentence++;
        }
    }
    return len;
}

int main(){
    char** text;
    int len_text, new_len;
    len_text = readText(&text, END_SENTENCE);
    new_len = len_text;
    new_len = deleteSentence(text, new_len);
    for(char** sentence = text; sentence < text + new_len; sentence++){
        printf("%s", *sentence);
        free(*sentence);
    }
    printf("Количество предложений до %d и количество предложений после %d\n", len_text - 1, new_len - 1);
    free(text);
    return 0;
}
