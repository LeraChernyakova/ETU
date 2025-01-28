#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char* takephrase(){
    int addmemory = 100;
    int lenphrase = 0, sym;
    char *phrase = malloc(addmemory*sizeof(char));
    sym = getchar();
    if (sym=='\n');
    else { if (sym!=' ' && sym!='\t') phrase[lenphrase++] = sym;}
    sym = getchar();
    if (sym!=' ' && sym!='\t') phrase[lenphrase++] = sym;
    do {
        sym = getchar();
        phrase[lenphrase++] = sym;
        if (lenphrase == addmemory) {
            addmemory += 100;
            phrase = realloc(phrase, addmemory);
        }
    } while (sym != '.' && sym != ';' && sym != '?' && sym != '!');
    phrase[lenphrase] = '\0';
    return phrase;
}


int suitable(char* phrase){
    int res =1;
 for (int i = 0; i < strlen(phrase)-1; i++){
     if (phrase[i] == '5' && phrase[i+1] == '5' && phrase[i+2] == '5' && isalnum(phrase[i-1])==0 && isalnum(phrase[i+3]) == 0 )
         res = 0;

 }
    return res;
}

int main() {
    int lengthh = 0, notinclud = 0;
    char* phrase, *end = "Dragon flew away!";
    int addmemory = 100;
    char** result = malloc(addmemory*sizeof(char*));

    do { phrase = takephrase();
        if (suitable(phrase)!=0) {
            result[lengthh-notinclud] = phrase;
            lengthh ++;
        }
        else {notinclud++;
            lengthh ++;}
        if ((lengthh - notinclud) == addmemory) {
            addmemory += 100;
            result= realloc(result, addmemory*sizeof(char*));
        }
    } while (strcmp(phrase, end));

    for (int i = 0; i < (lengthh - notinclud); i++){
        puts(result[i]);
        free(result[i]);
    }
    free(result);
    printf("Количество предложений до %d и количество предложений после %d\n", lengthh -1 ,lengthh- notinclud -1);
    return 0;
}
