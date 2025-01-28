#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_sent(){
    char ch;
    char *tmp_sent;
    char len = 0;
    int mem_add = 100;
    tmp_sent = malloc(100*sizeof(char));


    while (1){

        ch = getchar();
        tmp_sent[len] = ch;
        len += 1;
        if (ch == '?') return NULL;
        if ((ch == '.')||(ch == ';')||(ch == '?')||(ch == '!')) break;
        if (len > mem_add){
            mem_add += 100;
            tmp_sent = realloc(tmp_sent, mem_add);
        }

    }

    tmp_sent[len] = '\0';
    return tmp_sent;
}



char* sentence_edit_1(char* tmp_sent){
    int i = 0;
    while(tmp_sent[i] == ' ' || tmp_sent[i] == '\t' || tmp_sent[i] == '\n')
        {
            int j;
            for (j = 0; j < strlen(tmp_sent) - 1; j ++){
                tmp_sent[j] = tmp_sent[j+1];
        }
    
    tmp_sent[j] = '\0';
    
    }
    return tmp_sent;
}


int main(){

    char stop_sent[] = "Dragon flew away!";
    char **text = malloc(100*sizeof(char*));
    char *sentence;
    int i=0;
    int origin_str_count=0;
    int main_mem_add = 100;

    while (1){

        sentence = get_sent();
        origin_str_count += 1;
        if (sentence != NULL){

            sentence = sentence_edit_1(sentence);

            text[i] = sentence;
            i += 1;

            if (i == main_mem_add){
                main_mem_add += 100;
                text = realloc(text, (main_mem_add*sizeof(char*)));

            }

            if (!strcmp(stop_sent,sentence))
                break;
        }
    }
    for (int k=0;k<i; k++){
        printf("%s\n", text[k]);
        free(text[i]);
    }
    free(text);
    printf("Количество предложений до %d и количество предложений после %d\n", origin_str_count-1, i-1);

    return 0;
}