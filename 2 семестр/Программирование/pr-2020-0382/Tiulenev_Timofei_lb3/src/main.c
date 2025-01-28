#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* readstr();
int delete(char*);

int main() {
    int len = 0;
    int notlen = 0;
    char *str;
    char *end = "Dragon flew away!"; 
    int size = 2; 
    char** result = malloc(size*sizeof(char*));

    do { str = readstr();
        if (delete(str)==0) {
            notlen++;
            len ++;
        }
        else {
	result[len-notlen] = str;
              len ++;
       }
        if ((len - notlen) == size) {
            size += 255;
            result= realloc(result, size*sizeof(char*));
        }
    } while (strcmp(str, end));

    for (int i = 0; i < (len - notlen); i++){
        puts(result[i]);
        free(result[i]);
    }
    free(result);
    printf("Количество предложений до %d и количество предложений после %d\n", len -1 ,len- notlen -1);
    return 0;
}

char* readstr(){
    int size = 255;
    int lenstr = 0, sym;
    char *str = malloc(size*sizeof(char));
    sym = getchar();
    if (sym=='\n');
    else { if (sym!=' ' && sym!='\t') str[lenstr++] = sym;}
    sym = getchar();
    if (sym!=' ' && sym!='\t') str[lenstr++] = sym;
    do {
        sym = getchar();
        str[lenstr++] = sym;
        if (lenstr == size) {
            size += 255;
            str = realloc(str, size);
        }
    } while (sym != '.' && sym != ';' && sym != '?' && sym != '!');
    str[lenstr] = '\0';
    return str;
}


int delete(char* str){
    int x =1;
 for (int i = 0; i < strlen(str)-1; i++){
     if (isalnum(str[i-1])==0 &&str[i] == '5' && str[i+1] == '5' && str[i+2] == '5' &&  isalnum(str[i+3]) == 0 )
         x = 0;
 }
    return x;
}