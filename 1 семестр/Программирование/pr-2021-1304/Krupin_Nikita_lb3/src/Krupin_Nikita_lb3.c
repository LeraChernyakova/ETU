#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scan_text(char*** text, char* sep_str, char* end_sen) {
     int i_sen, i_ch;
    
    *text = NULL;
    i_sen = 0;
    do{
        *text = realloc(*text, sizeof(char*)*(i_sen+1));
        (*text)[i_sen] = NULL;
        i_ch = 0;
        
        scanf(" ");
        do {
            (*text)[i_sen] = realloc((*text)[i_sen], sizeof(char)*(i_ch+1));
            scanf("%c", (*text)[i_sen]+i_ch);
            i_ch++;
        } while (!strchr(sep_str, (*text)[i_sen][i_ch-1]));
        
        (*text)[i_sen] = realloc((*text)[i_sen], sizeof(char)*(i_ch+1));
        (*text)[i_sen][i_ch] = '\0';
        i_sen++;
    } while (strcmp((*text)[i_sen-1], end_sen));
    
    return i_sen;
}

int remove_questions(char** text, int count){
    char** sen;
    
    sen = text;
    while (sen < text+count)
        if (strchr(*sen, '?')){
            free(*sen);
            count--;
            memmove(sen, sen+1, sizeof(char*)*(text+count-sen));
        } else sen++;
    
    return count;
}

void print_text(char** text, int count, char* sep){
    char** sen;
    
    for (sen = text; sen < text+count; sen++)
        printf("%s%s", *sen, sep);
}

void free_text(char** text,  int count){
    char** sen;
    
    for (sen = text; sen < text+count; sen++)
        free(*sen);
    free(text);
}

int main(){
    char** text; int count, new_count;
    
    count = scan_text(&text, ";.?!", "Dragon flew away!");
    
    new_count = remove_questions(text, count);
    
    print_text(text, new_count, "\n");
    printf("Количество предложений до %d и количество предложений после %d", count-1, new_count-1);
    
    free_text(text, new_count);
    return 0;
}
