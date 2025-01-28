#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* print_string(char *s);
char** print_text(char **strs);

int n = 0; //до обработки
int m = 0; //после обработки
int sum_upper = 0;
char c;
int strs_index = 0;

char** print_text(char **strs){  //предложения
    int strsize = 10;
    while(1){
        if(strs_index==strsize){
            strsize+=10;
            strs = realloc(strs, strsize*sizeof(char*));
        }
        char* s = malloc(40*sizeof(char));
        s = print_string(s);
        if (s[0]==' ')
            s++;
        n++;
        if (sum_upper<=1){
            strs[strs_index++]=s;
            m++;
        }
        if (!strcmp(s, "Dragon flew away!")) {
            break;
        }
    }
    return strs;
}

char* print_string(char *s){  //символы
    int s_size = 40;
    int s_index = 0;
    sum_upper = 0;
    while(1){
        if(s_index==s_size-1){
            s_size+=40;
            s = realloc(s, s_size*sizeof(char));

        }
        c = getchar();
        if (isupper(c))
            sum_upper++;
        if (c!='\t' && c!='\n'){
            if (s!="" || c!=' '){
                s[s_index++]=c;
            }
        }
        if (c=='.' || c==';' || c=='?'){
            c=getchar();
            while (c=='\n')
                c = getchar();
            s[s_index]='\0';
            break;
        }
        if(c=='!'){
            s[s_index]='\0';
            break;
        }
    }
    return s;
}

int main() {
    char **strs = malloc(10*sizeof(char*));
    strs = print_text(strs);
    for (int i = 0; i<strs_index; i++){
        printf("%s\n", strs[i]);
        free(strs[i]);
    }
    free(strs);
    printf("Количество предложений до %d и количество предложений после %d", n-1, m-1);
    return 0;
}
