//lb3_prog.c

#include <stdio.h>
#include <stdlib.h>
#include  <ctype.h>
#include <string.h>

#define BASIC_LEN_SENT 50
#define BASIC_LEN_TEXT 20


char* get_sent(){

    char *sent, *re_sent;
    char ch = 0;
    int len_sent = 0;
    int max_len_sent =  BASIC_LEN_SENT;
    int in_sent = 0;

    sent = calloc(BASIC_LEN_SENT,sizeof(char));// незабудь free

    if (sent == NULL){
        fprintf(stderr,"Ошибка выделения памяти для sent");
        exit(1);
    }

    while ((ch != '.')&&(ch != ';')&&(ch != '?')&&(ch != '!')){
        ch = getchar();

        if ((ch != ' ')&&(ch != '\n')&&(in_sent == 0)){in_sent = 1;}

        if ((ch != '\n')&&(in_sent == 1)) {
            if (len_sent  == max_len_sent - 1) {

                max_len_sent = max_len_sent + BASIC_LEN_SENT;
                re_sent = realloc(sent, max_len_sent*sizeof(char));

                if (re_sent == NULL) {
                    free(sent);
                    fprintf(stderr, "Ошибка перевыделения памяти для sent");
                    exit(1);
                } else {
                    sent = re_sent;
                }
            }

            sent[len_sent] = ch;
            len_sent ++;
        }

    }
    sent[len_sent] = '\0';

    return sent;
}

int find_seven(char *sent){
    for (int i = 0; i<strlen(sent);i++){
        if (sent[i] == '7') {
            return 1;
        }
    }
    return 0;
}


int main (){
    char **text, **re_text ;
    char *sent = "";
    int len_text = 0,i,kol_sent_bef = 0;
    int max_len_text = BASIC_LEN_TEXT;

    text = malloc(BASIC_LEN_TEXT*sizeof(char*));

    if (text == NULL){
        fprintf(stderr,"Ошибка выделения памяти для Text");
        exit(1);
    }

    while (strcmp(sent , "Dragon flew away!")){
        sent = get_sent();
        kol_sent_bef ++;

        if (!find_seven(sent)) {
            if (len_text == max_len_text) {

                max_len_text = max_len_text + BASIC_LEN_TEXT;
                re_text = realloc(text, max_len_text*sizeof(char*));

                if (re_text == NULL) {
                    for (i = 0; i < len_text; i++) {
                        free(text[i]);
                    }
                    free(text);
                    free(sent);
                    fprintf(stderr, "Ошибка перевыделения памяти для Text");
                    exit(1);
                } else {
                    text = re_text;
                }
            }

            text[len_text] = sent;
            len_text++;
        }
    }

    for (int i = 0; i<len_text ; i++){
        printf("%s\n",text[i]);
    }
    printf("Количество предложений до %i и количество предложений после %i",kol_sent_bef-1,len_text-1);

    for (i = 0 ; i<len_text ;i++){
        free(text[i]);
    }
    free(text);


    return 0;


}




