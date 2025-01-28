#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define INIT_SIZE 50
#define TRUE 1

char* readsentence(){
    int size_sent = INIT_SIZE;
    int length = 0;

    char *sent = malloc(size_sent*sizeof(char));
    int c;

    while (TRUE){
        c = getchar();
	sent[length++]=c;
        if(length == size_sent){
            size_sent += INIT_SIZE;
            sent = realloc(sent, size_sent);
        }
        if(c == '.' || c == ';' || c == '?' || c == '!'){
            break;
        }
    }

    if(length>0){
        sent[length]='\0';
        return sent;
    }
}

int stop_input(char *sent1, char  *sent2){
    int a, i;
    for (i=0; i < strlen(sent2); i++){
        if (sent1[i] == sent2[i]){
            a = 1;
        }
        else{
            a = 0;
        }
    }
    return a;
}

char* delete_t(char *sent){
    int i = 0;
    int a = 0;
    while(sent[i] == ' ' || sent[i] == '\t' || sent[i] == '\n'){
	    int j;
	    for (j=0; j<strlen(sent)-1; j++){
		    sent[j] = sent[j+1];
	    }
	    a++;
    }
    sent[strlen(sent)-a] = '\0';

    return sent;
}

int delete_sent(char *sent){
    int a = 1;
    int i;
    for (i=0; i<strlen(sent)-3; i++){
        if ((sent[i] == '5') && (sent[i+1] == '5') && (sent[i+2] == '5') && (!(isalnum(sent[i-1]))) && (!(isalnum(sent[i+3])))){
            a = 0;
        }
    }
    return a;
}

int main(){
    int count1 = 0;
    int count2 = 0;
    char *sent;

    int size_text = INIT_SIZE;
    int len_text = 0;
    char** text = malloc(size_text*sizeof(char*));

    char* end_sent = "Dragon flew away!";
    while(TRUE){
        sent = readsentence();
        sent = delete_t(sent);
        count1++;
        if (delete_sent(sent)){
            count2++;
            text[len_text++] = sent;
        }
        if (len_text == size_text){
            size_text += INIT_SIZE;
            text = realloc(text, size_text*sizeof(char*));
        }
        if (stop_input(end_sent, sent)){
            break;
        }
    }

    for (int i = 0; i<len_text; i++){
        printf("%s\n", text[i]);
        free(text[i]);
    }
    free(text);
    
    printf("Количество предложений до %d и количество предложений после %d", count1-1, count2-1);
    
    return 0;

}
