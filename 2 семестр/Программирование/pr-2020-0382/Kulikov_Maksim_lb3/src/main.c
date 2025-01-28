#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* input_sentence(){
    int sentence_size = 100, sym_count = 0;
    char sym = '0';
    char* sentence = malloc(sentence_size * sizeof(char));
    while(sym != '.' && sym!= ';' && sym!= '?' && sym!= '!'){
        sym = (char)getchar();
        sentence[sym_count] = sym;
        sym_count += 1;
        if (sym_count == sentence_size){
            sentence_size += 100;
            sentence = realloc(sentence,sentence_size);
        }
    }
    sentence[sym_count] = '\0';
    return sentence;

}

int sentence_selection(char* sentence){
    int i;
    for(i = 0;i < strlen(sentence) - 1;i++){
        if(isdigit(sentence[i])){
            while(isdigit(sentence[i+1]) || isalpha(sentence[i+1]) ){
                if(isalpha(sentence[i+1])){
                    while(isdigit(sentence[i+2]) || isalpha(sentence[i+2]) ) {
                        if(isdigit(sentence[i+2]))
                            return 0;
                        i++;
                    }

                }
                i++;
            }

        }
        if(isalpha(sentence[i])){
            while(isdigit(sentence[i]) || isalpha(sentence[i]) ){
                if(isdigit(sentence[i])){
                    while(isdigit(sentence[i+1]) || isalpha(sentence[i+1]) ) {
                        if(isalpha(sentence[i+1]))
                            return 0;
                        i++;
                    }

                }
                i++;
            }
        }
    }



    return 1;
}


char* no_spaces(char* sentence){
    while(sentence[0] == ' ' || sentence[0] == '\t' || sentence[0] == '\n'){
        int i;
        for (i = 0; i < strlen(sentence) - 1; i++){
            sentence[i] = sentence[i+1];
        }
        sentence[i] = '\0';
    }
    return sentence;
}


int main(){
    int text_size = 10;
    int sent_before_count = 0, sent_after_count = 0;
    char** text = malloc(text_size * sizeof(char*));
    char* sentence;
    while(1){
        sentence = input_sentence();
        sentence = no_spaces(sentence);
        if(sentence_selection(sentence)) {
            text[sent_after_count] = sentence;
            sent_after_count++;
            if (!strcmp(text[sent_after_count - 1],"Dragon flew away!")){
                break;
            }
        }
        else
            free(sentence);
        sent_before_count += 1;
        if (sent_after_count == text_size ){
            text_size += 10;
            text = realloc(text,text_size * sizeof(char*));
        }
    }
    for(int i = 0; i < sent_after_count ; i++)
        printf("%s\n",text[i]);
    printf("Количество предложений до %d и количество предложений после %d",sent_before_count  ,sent_after_count - 1 );
    for(int i = 0; i < sent_after_count ; i++){
        free(text[i]);
    }
    free(text);
    return 0;

}







