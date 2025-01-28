#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct Words{
    char **word;
    int cur_size;
    int max_size;
};



int cmp(const void* p1, const void* p2){
    char *word1 = *((char**)p1);
    char *word2 = *((char**)p2);

    return strcmp(word1,word2);
}


int main(){
    char *str = malloc(1002 * sizeof(char));
    char *find_word = malloc(32 * sizeof(char));
    char **point;
    struct Words arr_words =  {.cur_size = 0};
    char* temp_p;
    int i;

    arr_words.max_size = 50;
    arr_words.word = malloc(arr_words.max_size * sizeof(char*));

    fgets(str,1002,stdin);
    fgets(find_word,32,stdin);

    str[strlen(str)-1] = '\0';

    temp_p = strtok(str," .");
    for (i = 0; temp_p ; i++){
        if (arr_words.cur_size == arr_words.max_size-2){
            arr_words.max_size = arr_words.max_size + 30;
            arr_words.word = realloc(arr_words.word,arr_words.max_size * sizeof(char*));
        }
        arr_words.word[i] = temp_p;
        arr_words.cur_size++;

        temp_p = strtok(NULL, " .");
    }

    qsort(arr_words.word,arr_words.cur_size,sizeof (char*),cmp);

    point = (char**)bsearch(&find_word,arr_words.word,arr_words.cur_size,sizeof (char*),cmp);


    if (point == NULL){
        printf("doesn't exist");
    }else{
        printf("exists");
    }

    free(find_word);
    free(str);
    free(arr_words.word);

}


