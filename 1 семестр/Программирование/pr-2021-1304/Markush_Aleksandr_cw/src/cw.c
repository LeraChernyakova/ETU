#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define SIZE 1
#define MEM_STEP 30
#define COMP_CHAR 4
#define WORDS_NUMBER 3000


char** get_text(int *text_size);
int del_repeats(char*** text, int text_size);
int del_sentences(char*** text, int text_size);
int sort_comparison(const void *s1,const void *s2);
void sorting(char**text, int text_size);
void reverse_words(char **text, int text_size);
void word_count(char** text, int text_size);
void text_print(char** text, int text_size);
void memory_free(char** text,int text_size);


char** get_text(int *text_size){
    int s = 0;
    int c = 0;
    char x;
    int s_length = MEM_STEP;
    int t_length = SIZE;
    char** text = malloc(t_length*sizeof(char*));
    if(text == NULL){
        puts("Memory error!");
        return NULL;
    }
    text[s] = malloc(s_length*sizeof(char));
    if(text[s] == NULL){
        puts("Memory error!");
        return NULL;
    }
    while((x = getchar()) != '\n'){
        if(s == t_length){
            t_length += SIZE;
            text = realloc(text, sizeof(char*)*t_length);
            if(text == NULL){
                puts("Memory error!");
                return NULL;
            }
            text[s] = malloc(s_length*sizeof(char));
            if(text[s] == NULL){
                puts("Memory error!");
                return NULL;
            }
        }
        if(c + 1 == s_length){
            s_length += MEM_STEP;
            text[s] = realloc(text[s], sizeof(char)*s_length);
            if(text[s] == NULL){
                puts("Memory error!");
                return NULL;
            }
        }
        text[s][c] = x;
        c++;
        if(x == '.'){
            text[s][c] = '\0';
            s++;
            s_length = MEM_STEP;
            c = 0;
        }
    }
    *text_size = s;
    return text;
}


int del_repeats(char*** text, int text_size){
    int i = 0;
    while(i < text_size){
        int count = 0;
        int j = i+1;
        while(j < text_size){
            if(!strcasecmp((*text)[i], (*text)[j])){
                count = 1;
                free((*text)[j]);
                for(int k = j; k < text_size - 1; k++){
                    (*text)[k] = (*text)[k + 1];
                }
                text_size--;
            }
            else{
                j++;
            }
        }
        if(count != 0){
            free((*text)[i]);
            for(int j = i; j < text_size -1; j++){
                (*text)[j] = (*text)[j + 1];
            }
            text_size--;
        }
        else{
            i++;
        }
    }
    return text_size;
}


int del_sentences(char*** text, int text_size){
    int count;
    int i = 0;
    while(i < text_size){
        count = 0;
        for(int j = 0; j < strlen((*text)[i]); j++){
            if((*text)[i][j] == ','){
                count++;
            }
        }
        if(count >= 1){
            free((*text)[i]);
            for(int j = i; j < text_size - 1; j++){
                (*text)[j] = (*text)[j + 1];
            }
            text_size--;
        }
        else{
            i++;
        }
    }
    return text_size;
}


int sort_comparison(const void *s1,const void *s2){
    char *str1 = *(char**)s1;
    char *str2 = *(char**)s2;
    int ord1;
    int ord2;
    if(strlen(str1) < 5){
        ord1 = -1;
    }
    else{
        if(str1[COMP_CHAR] == ',' || str1[COMP_CHAR] == ' '){
            ord1 = str1[COMP_CHAR+1];
        }
        else{
            ord1 = str1[COMP_CHAR];
        }
    }
    if(strlen(str2) < 5){
        ord2 = -1;
    }
    else{
        if(str2[COMP_CHAR] == ',' || str2[COMP_CHAR] == ' '){
            ord2 = str2[COMP_CHAR+1];
        }
        else{
            ord2 = str2[COMP_CHAR];
        }
    }
    if(ord1 > ord2){
        return -1;
    }
    else if(ord1 < ord2){
        return 1;
    }
    return 0;
}


void sorting(char**text, int text_size){
    qsort(text, text_size, sizeof(char*), sort_comparison);
}


void reverse_words(char **text, int text_size){
    char *first_letter;
    char *last_letter;
    for(int i = 0; i < text_size; i++){
        char c;
        int x;
        int begin = 0;
        first_letter = &text[i][0];
        for(int j = 0; j < strlen(text[i]); j++){
            if((text[i][j] == '.') || (text[i][j] == ',') || (text[i][j] == ' ')){
                last_letter = &text[i][j-1];
                x = 0;
                while(((j - begin)/2) != x){
                    c = *(first_letter + x);
                    *(first_letter + x) = *(last_letter - x);
                    *(last_letter - x) = c;
                    x++;
                }
                first_letter = &text[i][j+1];
                begin = j+1;
            }
        }
    }
}


void word_count(char** text, int text_size){
    char** words;
    int words_len = 0;
    char *first_letter;
    words = malloc(WORDS_NUMBER*sizeof(char*));
    if(words == NULL){
        puts("Memory error!");
    }
    int count[WORDS_NUMBER];
    for(int i = 0; i < text_size; i++){
        int x;
        int begin = 0;
        first_letter = &text[i][0];
        for(int j = 0; j < strlen(text[i]); j++){
            if((text[i][j] == '.') || (text[i][j] == ',') || (text[i][j] == ' ')){
		if(j == 0){
		    first_letter = &text[i][j+1];
                    begin = j+1;
		    continue;
		}    
                char* word = malloc((j-begin+1)*sizeof(char));
                if(word == NULL){
                    puts("Memory error!");
                }
                x = 0;
                while(((j - begin)) != x){
                    word[x] = *(first_letter + x);
                    x++;
                    if(x == j - begin){
                        word[x] = '\0';
                    }
                }
                if(words_len == 0){
                    words[0] = word;
                    count[0] = 0;
                    words_len++;
                }
                int z = words_len;
                int n = 0;
                for(int k = 0; k < z; k++){
                    if(!strcmp(word, words[k])){
                        count[k]++;
                        n = 1;
                    }
                }
                if(n == 0){
                    words[words_len] = word;
                    count[words_len] = 1;
                    words_len++;
                }
                first_letter = &text[i][j+1];
                begin = j+1;
            }
        }
    }
    for(int i = 0; i < words_len; i++){
        printf("%s : %d\n", words[i], count[i]);
    }
    memory_free(words, words_len);
}


void memory_free(char** text, int text_size){
    for(int i = 0; i < text_size; i++){
        free(text[i]);
    }
    free(text);
}


void text_print(char** text, int text_size){
    for(int i = 0; i < text_size; i++){
        printf("%s", text[i]);
    }
    puts("");
}


int main(){
    setlocale(LC_ALL, "Russian");
    int text_size = 0;
    puts("Введите пожалуйста текст.");
    char **text = get_text(&text_size);
    text_size = del_repeats(&text, text_size);
    puts("");
    puts("Доступные действия:");
    puts("1)Распечатать каждое слово и количество его повторений в тексте.");
    puts("2)Преобразовать каждое предложение так, что символы в каждом слове шли в обратном порядке.");
    puts("3)Удалить предложения в котором встречается запятая.");
    puts("4)Отсортировать предложения по уменьшению значения кода 5 символа предложения.");
    puts("5)Выйти из программы.\n");
    int end = 0;
    while(end == 0){
        printf("Выберите действие: ");
        int move;
        scanf("%d", &move);
        puts("");
        switch(move){
            case 1:
                word_count(text, text_size);
                puts("\n------------------------------------------------------------------------");
                break;
            case 2:
                reverse_words(text, text_size);
                text_print(text, text_size);
                puts("\n------------------------------------------------------------------------");
                break;
            case 3:
                text_size = del_sentences(&text, text_size);
                text_print(text, text_size);
                puts("\n------------------------------------------------------------------------");
                break;
            case 4:
                sorting(text, text_size);
                text_print(text, text_size);
                puts("\n------------------------------------------------------------------------");
                break;
            case 5:
                puts("Работа программы завершена.");
                end = 1;
                break;
            default:
                puts("Данной команды не существует!");
                end = 1;
                break;
        }
    }
    memory_free(text, text_size);

    return 0;
}

