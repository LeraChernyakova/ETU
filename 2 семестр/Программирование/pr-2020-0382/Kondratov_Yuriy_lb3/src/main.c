#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define TEXT_STEP 50
#define SENT_STEP 100

char* get_sentence(){
    int sent_mem_size = SENT_STEP;
    int sent_length = 0;
    int sym;

    char *sentence = malloc(sent_mem_size*sizeof(char));

    while (TRUE) {
        sym = getchar();
        sentence[sent_length++] = sym;
        if (sym == '.' || sym == ';' || sym == '?' || sym == '!') break;

        if (sent_length == sent_mem_size) {
            sent_mem_size += SENT_STEP;
            sentence = realloc(sentence, sent_mem_size);
        }
    }

    sentence[sent_length] = '\0';
    return sentence;
}

char* space_cut(char* sent){
    int i = 0;
    while(sent[i] == ' ' || sent[i] == '\t' || sent[i] == '\n'){
        int j;
        for (j = 0; j < strlen(sent) - 1; j ++){
            sent[j] = sent[j+1];
        }
        sent[j] = '\0';
    }
    return sent;
}

int is_sent_ok (char* sent){

    int ans = TRUE;
    int in_word = FALSE;

    for (int i = 0; i < strlen(sent)-1; i ++) {
        if (!isalnum(sent[i])) {
            in_word = FALSE;
        }
        else {
            if (isdigit(sent[i])) {
                if (!in_word){
                    if (isalpha(sent[i+1])){
                        in_word = TRUE;
                    }
                    else{
                        int j = 1;
                        while (isalnum(sent[i+j])) {
                            if (isdigit(sent[i+j])){
                                j++;
                            }
                            else{
                                ans = FALSE;
                                break;
                            }
                        }
                        i += j;
                    }
                }
                else{
                    if (isalnum(sent[i+1])){
                        ans = FALSE;
                        break;
                    }
                }
            }
            else{
                in_word = TRUE;
            }
        }
    }
    return ans;
}

int main() {
    int text_len = 0;
    int wrong_count = 0;
    char* end_sent = "Dragon flew away!";

    int text_mem_size = TEXT_STEP;
    char** text = malloc(text_mem_size*sizeof(char*));

    char* sentence;

    while (TRUE) {
        sentence = get_sentence();
        sentence = space_cut(sentence);

        if (is_sent_ok(sentence)) {
            text[text_len++] = sentence;
        }
        else wrong_count += 1;

        if (text_len == text_mem_size) {
            text_mem_size += TEXT_STEP;
            text = realloc(text, text_mem_size*sizeof(char*));
        }

        if (!strcmp(sentence, end_sent)) break;
    }

    for (int i = 0; i < text_len; i++){
        puts(text[i]);
        free(text[i]);
    }
    free(text);

    printf("Количество предложений до %d и количество предложений после %d\n", text_len+wrong_count-1, text_len-1);
    return 0;
}
