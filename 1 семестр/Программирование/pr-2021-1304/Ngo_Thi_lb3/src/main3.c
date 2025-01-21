#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int in_word(char*** word, char* fisrt_str, char* end_sep) {
    int i_str, i_ch;
    *word = NULL;
    i_str = 0;
    do{
        *word= realloc(*word, sizeof(char*)*(i_str+1));
        (*word)[i_str] = NULL;
        i_ch = 0;

        scanf(" ");
        do {
            (*word)[i_str] = realloc((*word)[i_str], sizeof(char)*(i_ch+1));
            scanf("%c", (*word)[i_str]+i_ch);
            i_ch++;
        } while (!strchr(fisrt_str, (*word)[i_str][i_ch-1]));
        (*word)[i_str] = realloc((*word)[i_str], sizeof(char)*(i_ch+1));
        (*word)[i_str][i_ch] = '\0';
        i_str++;
    } while (strcmp((*word)[i_str-1], end_sep));

    return i_str;
}


int remove_questions(char** word, int count){
    char** ans;
    ans = word;
    while (ans < word + count)
        if (strchr(*ans, '?')){
            free(*ans);
            count--;
            memmove(ans, ans+1, sizeof(char*)*(word+count-ans));
        } else ans++;

    return count;
}


void out_word(char** word, int count, char* str){
    char** ans;
    for (ans = word; ans < word+count; ans++)
        printf("%s%s", *ans, str);
}

void free_word(char** word,  int count){
    char** ans;

    for (ans = word; ans < word+count; ans++)
        free(*ans);
    free(word);
}


int main(){
    char** word; int result, new_result;
    result = in_word(&word, ";.?!", "Dragon flew away!");
    new_result = remove_questions(word, result);
    out_word(word, new_result, "\n");
    printf("Количество предложений до %d и количество предложений после %d", result-1, new_result-1);

    free_word(word, new_result-1);
    return 0;
}
