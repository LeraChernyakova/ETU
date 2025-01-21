#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_text(char*** text){
    int s_number = 0;
    *text = NULL;
    do{
        *text = realloc(*text, sizeof(char*)*(s_number+1));
        int c_number = 0;
        (*text)[s_number] = NULL;
        (*text)[s_number] = malloc(sizeof(char)*(c_number+1));
        scanf(" ");
        do{
            scanf("%c", &(*text)[s_number][c_number]);
            c_number++;
            (*text)[s_number] = realloc((*text)[s_number], sizeof(char)*(c_number+1));
        }while(((*text)[s_number][c_number-1] != '!') && ((*text)[s_number][c_number-1] != '?') && ((*text)[s_number][c_number-1] != '.') && ((*text)[s_number][c_number-1] != ';'));

        (*text)[s_number][c_number] = '\0';
        s_number++;
    }while(strcmp((*text)[s_number-1], "Dragon flew away!") != 0);

    return s_number;
}

int del_sentences(char*** text, int text_size){

    char** n_text = NULL;
    int n_size = 0;

    for(int i = 0; i < text_size; i++){
        int count = 0;
        for(int j = 0; j < strlen((*text)[i]); j++){
            if((*text)[i][j] > 64 && (*text)[i][j] < 91){
                count++;
            }
        }
        if(count > 1){
            free((*text)[i]);
        }
        else{
            n_text = realloc(n_text, sizeof(char*)*(n_size+1));
            n_text[n_size] = (*text)[i];
            n_size++;
        }
    }
    free(*text);
    *text = n_text;
    return n_size;

}

void print_text(char **text, int pr_size, int new_size){
    for(int i = 0; i < new_size; i++){
        printf("%s\n", text[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d\n", pr_size-1, new_size-1);
}

void free_text(char ***text, int size){

    for(int i = 0; i < size; i++){
        free((*text)[i]);
    }
    free((*text));

}


int main(){
    char **text;
    int text_size = get_text(&text);
    int new_size = del_sentences(&text, text_size);

    print_text(text, text_size, new_size);
    free_text(&text, new_size);

    return 0;
}
