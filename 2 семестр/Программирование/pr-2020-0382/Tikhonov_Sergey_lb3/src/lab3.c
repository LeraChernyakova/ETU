#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char* get_sentences(){
    int sentences_size=100;
    int sentences_len=0;
    int sign;
    char*sentences=malloc(sentences_size*sizeof(char));
    int b=1;
    while (b==1){
        sign=getchar();
        sentences[sentences_len++]=sign;
        if (sign=='.' || sign=='!' || sign=='?' || sign==';') break;
        if(sentences_len==sentences_size){
            sentences_size=sentences_size*2;
            sentences=realloc(sentences, sentences_size);
        }
    }
 sentences[sentences_len]='\0';
    return sentences;
}
char* removing_spaces(char*sentences){
    int i=0;
    while (sentences[i]==' ' || sentences[i]=='\n' || sentences[i]=='\t') {
        int j;
        for (j = 0; j < strlen(sentences) - 1; j++) {
            sentences[j] = sentences[j + 1];
        }
        sentences[j]='\0';
    }
    return sentences;
}
int normal_offer(char *sentences){
    int true=1;
    int false=0;
    for (int i=0; i<strlen(sentences)-1; i++){
        if (!isalnum(sentences[i])){
            false=0;
        }
        else {
            if (isdigit(sentences[i])){
                if(!false){
                    if(isalpha(sentences[i+1])){
                        false=1;
                    }
                    else {
                        int j=1;
                        while (isalnum(sentences[i+j])){
                            if (isdigit(sentences[i+j])){
                                j++;
                            }
                            else{
                                true=0;
                                break;
                            }
                        }
                        i+=j;
                    }
                }
                else{
                    if (isalnum(sentences[i+1])){
                        true=0;
                        break;
                    }
                }
            }
            else{
                false=1;
            }
        }
    }
    return true;
}
int main(){
    int text_len=0;
    int wrong_sentences=0;
    char* end_text= "Dragon flew away!";
    int text_size =60;
    char**text=malloc(text_size*sizeof(char*));
    char*sentences;
    int a=1;
    while (a==1){
        sentences=get_sentences();
        sentences= removing_spaces(sentences);
        if (normal_offer(sentences)){
        text[text_len++]=sentences;
        }
        else wrong_sentences +=1;
        if (text_len==text_size){
            text_size=text_size*2;
            text=realloc(text, text_size*sizeof(char*));
        }
        if(!strcmp(sentences, end_text)) break;
    }
    for (int i=0; i<text_len; i++){
        puts (text[i]);
        free(text[i]);
    }
    free(text);
    printf("Количество предложений до %d и количество предложений после %d\n", text_len+wrong_sentences-1, text_len-1);
    return 0;
}
