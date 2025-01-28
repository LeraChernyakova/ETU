#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define RED  "\033[0;31m"
#define NONE "\033[0m"

char* get_text(){
    int length = 0;
    char sym = 0;
    char *text = malloc(1*sizeof(char));
    sym = getchar();
    if(sym!=' ' && sym!='\t'){
        text[length] = sym;
        length++;
    }
    while (sym != '.' && sym != '\n'){
        sym = getchar();
        if (sym!='\t' && sym!='\n'){
            text[length] = sym;
            length++;
            text= realloc(text,(length+1)*sizeof(char*));
        }
    }
    text[length] = '\0';
    return text;
}
char* word_length(char* text){
    int i=0;
    int m=0;
    char *res= malloc(1*sizeof(char));
    while (text[i]!='.') {
        int begin = i;
        int count = 0;
        while (1)
        {
            i++;
            if (text[i] == ' ' || text[i] == ','|| text[i] == '.') {
                break;
            }
        }
        if (text[i+1] == ' '){
            i++;
        }
        for(int l=begin;l<i; l++)
            if (isalpha(text[l])) {
                count++;
            }
        if (count==0){
            for(int k = begin; k<=i; k++ ){
                res = realloc(res,(m*2)*sizeof(char));
                res[m]=text[k];
                m++;
            }
        }
        else{
            char *base=malloc(10*sizeof(char));
            int u=0;
            while (count>0)
            {
                base[u]=48+(count%10);
                count=count/10;
                u++;
            }
            base[u]='\0';
            for (u=0;u<strlen(base)/2;u++)
            {
                char temp;
                temp=base[u];
                base[u]=base[strlen(base)-1-u];
                base[strlen(base)-1-u]=temp;
            }
            res[m]=base[0];
            m++;
            if (strlen(base)>1){
                res[m]=base[1];
                m++;
            }
            free(base);
            res = realloc(res,(m*2)*sizeof(char));
            for(int k = begin; k<=i; k++ ){
                res = realloc(res,(m*2)*sizeof(char));
                res[m]=text[k];
                m++;
            }

        }
        i++;
        if (text[i-1] == '.') {
            break;
        }
    }
    res = realloc(res,(m*2)*sizeof(char));
    res[m]="\0";
    return res;
}
int data(char *text){
    time_t rawtime;
    time(&rawtime);
    struct tm * timeinfo;
    timeinfo = localtime(&rawtime);
    int i = 0;
    int flag = 2;
    int base=0;
    int consent = 0;
    int chek=0;
    int d = 0;
    int m = 0;
    int y = 0;
    int begin= 0;
    char* dd = malloc(3*(sizeof(char)));
    char* mm = malloc(3*(sizeof(char)));
    char* yy = malloc(5*(sizeof(char)));
    while (text[i]!='.') {
        begin=i-base;
        while (text[i] != '.') {
            if (text[i] == '/') {
                chek=1;
                break;
            }
            if (text[i] == '.') {
                break;
            }
            i++;
        }
        if(chek==0){
            break;
        }
        if ((strlen(text) >= i + 7) && (strlen(text) - 2 - i >= 0)) {
            if (isdigit(text[i - 2]) && isdigit(text[i - 1])) {
                if (isdigit(text[i + 1]) && isdigit(text[i + 2])) {
                    if (isdigit(text[i + 4]) && isdigit(text[i + 5]) && isdigit(text[i + 6]) && isdigit(text[i + 7])) {
                        consent=1;
                        flag=1;
                        dd[0] = text[i - 2];
                        dd[1] = text[i - 1];
                        dd[2] = "\0";
                        d = atoi(dd);
                        mm[0] = text[i + 1];
                        mm[1] = text[i + 2];
                        mm[2] = "\0";
                        m = atoi(mm);
                        yy[0] = text[i + 4];
                        yy[1] = text[i + 5];
                        yy[2] = text[i + 6];
                        yy[3] = text[i + 7];
                        yy[4] = '\0';
                        y = atoi(yy);
                        if ((y - 1900) > (timeinfo->tm_year)) {
                            flag = 0;
                        }
                        if ((y - 1900) == (timeinfo->tm_year)) {
                            if ((m - 1) > (timeinfo->tm_mon)) {
                                flag = 0;
                            }
                            if ((m - 1) == (timeinfo->tm_mon)) {
                                if ((d) > (timeinfo->tm_mday)) {
                                    flag = 0;
                                }
                            }
                        }
                    }
                }
            }
            if (flag==2){
                i=i+1;
            }
        }

        if (consent == 1) {
            if (flag==2){
                for (int n = begin; n <= i; n++) {
                    printf("%c", text[n]);
                }
                i=i+1;
                if (text[i-1] == '.') {
                    break;
                }
            }

            if (flag == 1) {
                for (int g = begin; g <= i + 7; g++) {
                    printf("%c", text[g]);
                }
                i = i + 8;
                base=0;
                if (text[i] == '.') {
                    printf(".");
                    break;
                }
            }
            if (flag == 0) {
                for (int g = begin; g < i - 2; g++) {
                    printf("%c", text[g]);
                }
                for (int l = i - 2; l <= i + 7; l++) {
                    printf("%s%c%s", RED, text[l], NONE);
                }
                i = i + 8;
                base=0;
                if (text[i] == '.') {
                    printf(".");
                    break;
                }
            }
            flag = 2;
        }
        else{
            i++;
            base=i;
            if (i > strlen(text)) {
                break;
            }
        }

    }
    free(dd);
    free(mm);
    free(yy);
    if (consent==1){
        printf("\n");
    }
    else{
        return 1;
    }
}

int deletion(char *text){
    int i=0;
    int count = 0;
    int flag = 1;
    while (text[i]!='.'){
        count=0;
        while(1){

            if (text[i]==' ' | text[i]==',' | text[i]=='.'){
                break;
            }
            if(isalpha(text[i])) {
                count++;
            }
            i++;
        }
        if(text[i+1]==' '){
            i++;
        }
        if ((count)%2==0){
            flag = 0;
        }
        i++;
        if (text[i-1] == '.') {
            break;
        }
    }
    return flag;

}
int comp(const void* it1, const void* it2){
    int len1 = 0;
    int len2 = 0;
    int i = 0;
    int j = 0;
    char** item1=(char **)it1;
    char** item2=(char **)it2;
    char* text1=*item1;
    char* text2=*item2;
    while (*(text1+len1)!='.'){
        len1++;
    }
    while (*(text2+len2)!='.'){
        len2++;
    }
    len1=len1-1;
    len2=len2-1;
    int count1=0;
    int count2=0;
    for(i = len1; i>=0; i--){
        if(isalpha(text1[i])){
            count1++;
        }
        if ((text1[i])==' ' | (text1[i])==','){
            break;
        }
    }
    for(j = len2; j>=0; j--){
        if(isalpha(text2[j])){
            count2++;
        }
        if ((text2[j])==' ' | (text2[j])==','){
            break;
        }
    }
    if (count1>=count2){
        return 1;
    }
    else {
        return -1;
    }
}

int main(){
    printf("Пожалуйста, введите текст, для дальнейшей обработки.\n"
           "(Для завершения ввода необходимо нажать 'enter')\n ");
    int after= 0;
    char* sentense;
    char** for_check = malloc(1*sizeof(char*));
    while (strcmp(sentense,"\n")){
        sentense=get_text();
        for_check[after] = sentense;
        after++;
        for_check = realloc(for_check, (after+1)*sizeof(char*));
    }
    int j = 0;
    char** text = malloc((after)*sizeof(char*));
    for (int i = 0; i<=after-2; i++){
        int k=1;
        for (int h = i+1; h<=after-1; h++ ){
            if (!strncasecmp(for_check[i],for_check[h],strlen(for_check[i]))){
                k=0;
                break;
            }
        }
        if (k==1){
            text[j]=for_check[i];
            j++;
        }
    }
    int n;
    int l=0;
    printf("Для совершения необходимого действия выберете соответсвующую команду:\n"
           "'1' - Вывести все предложения в которых есть даты в формате\n"
           "“DD/MM/YYYY”, даты которые еще не наступили будут выделены красным\n"
           "цветом;\n"
           "'2' - Удалить все предложения в которых каждое слово содержит \n"
           "нечетное количество букв;\n"
           "'3' - Преобразовать предложения так, чтобы перед каждым словом стояло\n"
           "количество букв в нем;\n"
           "'4' - Отсортировать предложения по возрастанию длины последнего слова;\n"
           "'5' - Вывод текста в текущем состоянии;\n"
           "'0' - Выход из программы.\n");
    while(1) {
        printf("Введите команду: ");
        scanf("%d", &n);
        switch (n) {
            case 0:
                free(for_check);
                free(text);
                printf("Работа программы завершена.\n");
                return 0;
            case 1:
                for (int i = 0; i < j; i++) {
                    data(text[i]);
                }
                break;
            case 2:
                l = 0;
                for (int i = 0; i < j; i++) {
                    if (deletion(text[i]) == 0) {
                        text[l] = text[i];
                        l++;
                    }
                }
                j=l;
                break;
            case 3:
                for (int i = 0; i < j; i++) {
                    text[i] = word_length(text[i]);
                }
                break;
            case 4:
                qsort(text, j, sizeof(char *), comp);
                break;
            case 5:
                for (int i = 0; i < j; i++) {
                    puts(text[i]);
                }
                break;
            default:
                printf("Данные некорректны\n");
                break;
        }
    }
}
