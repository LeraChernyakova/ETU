#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define INIT_SIZE 50
#define DELTA 50 
#define TRUE 1

char* readSentence() {
    int size = INIT_SIZE;
    int length = 0;
    char *text = malloc(size * sizeof(char));
    int c;

    while (TRUE) {
        c = getchar();
        text[length++] = c;
        if (length == size) {
            size += DELTA;
            text = realloc(text, size);
        }
        if (c == '.' || c == ';' || c == '?' || c == '!') {
            break;
        }
    }

    if (length > 0) {
        text[length] = '\0';
        return text;
    }
}

int stop_input(char* str1, char* str2) {
    int fact, i;
    for (i = 0; i < strlen(str2); i++) {
        if (str1[i] == str2[i]) {
            fact = 1;
        }
        else {
            fact = 0;
        }
    }
    return fact;
}

char* delete_tab(char *str) {
    int i = 0;
    int k = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
        int j;
        for (j = 0; j < strlen(str) - 1; j++) {
            str[j] = str[j + 1];
        }
        k++;
    }
    str[strlen(str) - k] = '\0';
    return str;
}



int extra(char *str) {
    int i = 0;
    int k = 1;
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == '?') {
            k = 0;
        }
    }
    return k;
}

int main() {
    char *txt;
    int size_arr = INIT_SIZE;
    char** arr_txt = malloc(size_arr * sizeof(char*));
    int len_arr = 0;
    int n = 0, m = 0;
    char* end = "Dragon flew away!";
    while (TRUE) {
        txt = readSentence();
        txt = delete_tab(txt);
        n++;

        if (extra(txt)) {
            m++;
            arr_txt[len_arr++] = txt;
        }

        if (len_arr == size_arr) {
            size_arr += DELTA;
            arr_txt = realloc(arr_txt, size_arr * sizeof(char*));
        }

        if (stop_input(end, txt)) {
            break;
        }
    }
    for (int i = 0; i < len_arr; i++) {
        puts(arr_txt[i]);
        free(arr_txt[i]);
    }
    free(arr_txt);
   

    printf("Количество предложений до %d и количество предложений после %d", n - 1, m- 1);

    return 0;
}
