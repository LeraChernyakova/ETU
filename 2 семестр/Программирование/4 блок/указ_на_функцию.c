#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char* read_sentence(char sep){
    char* sentence;
    int count_char = 0;
    int memory_for_char = 50;
    char c;
    char* t = malloc(memory_for_char * sizeof(char));
    if (t != NULL){
        sentence = t;
    }
    else{
        puts("Ошибка! Недостаточно памяти!");
        return NULL;
    }
    do{

        if (count_char == memory_for_char){
    		memory_for_char += 10;
            t = realloc(sentence, memory_for_char * sizeof(char));
            if(t != NULL){
    		    sentence = t;
            }
            else{
                puts("Ошибка! Недостаточно памяти!");
                return NULL;
            }
    	}
        c = getchar();
        if ((c != '\t') && (c != ' ')){
            sentence[count_char++] = c;
        }
        else{
            if ((c == ' ') && (count_char != 0)){
                sentence[count_char++] = c;
            }
        }
    }while(sentence[count_char-1] != sep);
    sentence[count_char] = '\0';
    return sentence;
}

int read_text(char*** text, char sep){

    int count_sentence = 0;
    int memory = 10;
    char* sentence;
    char** t = malloc(memory*sizeof(char*));
    if(t != NULL){
        *text = t ;
    }
    else{
        puts("Ошибка! Недостаточно памяти!");
        return 0;
    }

    do{
        sentence = read_sentence(sep);
        (*text)[count_sentence++] = sentence;

        if (count_sentence == memory){
    		memory += 10;
            t = realloc(*text, memory * sizeof(char*));
            if (t != NULL){
    		    *text = t;
    		}
            else{
                puts("Ошибка! Недостаточно памяти!");
                return 0;
            }
        }

    }while(getchar() != '\n');
    return count_sentence;
}


void print_text(char** text, int sentence){

    for(int i = 0; i < sentence; i++){
        printf("%s ",text[i]);
    }
    printf("\n\n");
}

void free_memory(char*** text, int sentence){

    for(int i = 0; i < sentence; i++){
        free((*text)[i]);
    }

    free((*text));

}

int main(){
    char** text;
    char sep = '. ';
    int len = read_text(&text, sep);

}
