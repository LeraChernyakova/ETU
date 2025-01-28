#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define StringSupply 50
#define TextSupply 20
char* get_string(char *s);
char** get_text(char **strs);
int sizebefore = 0, sizeafter = 0;
int counterABC = 0;
char c;
int strsindex = 0;

int main() {

    char **strs = malloc(20*sizeof(char*));
    strs = get_text(strs);
    for (int i = 0; i<strsindex; i++){
        printf("%s\n", strs[i]);
        free(strs[i]);
    }
    free(strs);
    printf("Количество предложений до %d и количество предложений после %d", sizebefore-1, sizeafter-1);

    return 0;
}
char** get_text(char **strs){
    int strsize = TextSupply;
    while(1){
        if(strsindex==strsize){
            strsize+=TextSupply;
            strs = realloc(strs, strsize*sizeof(char*));

        }
        char* s = malloc(StringSupply*sizeof(char));
        s = get_string(s);
        if (s[0]==' ')
            s++;
        sizebefore++;
        if (counterABC<=1){
            strs[strsindex++]=s;
            sizeafter++;
        }
        if (!strcmp(s, "Dragon flew away!")) {
            break;
        }
    }
    return strs;
}
char* get_string(char *s){
    int ssize = StringSupply;
    int sindex = 0;
    counterABC = 0;
    while(1){
        if(sindex==ssize-1){
            ssize+=StringSupply;
            s = realloc(s, ssize*sizeof(char));

        }
        c = getchar();
        if (isupper(c))
            counterABC++;
        if (c!='\t' && c!='\n'){
            if (s!="" || c!=' '){
                s[sindex++]=c;
            }
        }
        if (c=='.' || c==';' || c=='?'){
            c=getchar();
            while (c=='\n')
                c = getchar();
            s[sindex]='\0';
            break;
        }
        if(c=='!'){
            s[sindex]='\0';
            break;
        }
    }
    return s;
}
