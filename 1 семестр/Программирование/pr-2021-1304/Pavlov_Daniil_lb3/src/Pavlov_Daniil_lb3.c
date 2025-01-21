#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define END "Dragon flew away!\n"


int is_num_in_sentence(char* sentence)
{
    if ((strcmp(sentence, "555.") == 0) || (strcmp(sentence, "555;") == 0) || (strcmp(sentence, "555?") == 0) || (((strstr(sentence, "555 ") != NULL)) && (sentence[0] == '5') && (sentence[1] == '5') && (sentence[2]) == '5')){
        return 1;
    }
    if ((strstr(sentence, " 555 ") != NULL) || ((strstr(sentence, " 555,")) != NULL) || (strstr(sentence, " 555.")) != NULL || (strstr(sentence, " 555?")) || ((strstr(sentence, " 555;")) != NULL)){
        return 1;
    }else{
        return 0;
    }
}



void print_text(char **text)
{
    int i;

    for (i = 0; i >= 0; i++){
        if (is_num_in_sentence(text[i]) == 0){
            printf("%s", text[i]);
        }

        if (strcmp(text[i], END) == 0){
            break;
        }
    }
}


int sentences_count(char** text)
{
    int i;
    int counter = 0;

    for (i = 0; i>= 0; i++){
        if (strcmp(text[i], END) == 0){
            counter++;
            break;
        }else{
            counter++;
        }
    }

    return counter;
}

int sentence_count_with_num(char **text)
{
    int i;
    int counter = 0;

    for (i=0; i>=0; i++) {
        if (is_num_in_sentence(text[i]) == 1){
            counter++;
        }

        if (strcmp(text[i], END) == 0) {
            break;
        }
    }

    return counter;
}


void free_text(char** text, int I){

    for (int i = 0; i < I; i++)
        free(text[i]);
    free(text);
}


char** formating_text(char **text)
{
    int i = 0;

    do{
        text = realloc(text, sizeof(char *) * (i + 1));
        text[i] = NULL;
        scanf(" ");

        int j = 0;
        do {
            text[i] = realloc(text[i], (j + 1) * sizeof(char));
            text[i][j] = getchar();

            if ((text[i][j] == '\n') && (text[i][j-1] != ' ')) {
                text[i][j] = ' ';
            }else if ((text[i][j] == '\n') && (text[i][j-1] == ' ')){
                continue;
            }

            if ((text[i][j] == '.') || (text[i][j] == '?') || (text[i][j] == ';') || (text[i][j] == '!')){
                text[i] = realloc(text[i], (j + 3) * sizeof(char));
                text[i][j+1] = '\n';
                text[i][j+2] = '\0';
                break;
            }
            j++;


        }while (1);

        i++;
    }while (strcmp(text[i-1], END) != 0);

    return  text;
}


int main()
{
    char **sentences = NULL;
    int sents_amount;
    int sents_with_num;

    sentences = formating_text(sentences);
    print_text(sentences);
    sents_amount = sentences_count(sentences);
    sents_with_num = sentence_count_with_num(sentences);


    printf("Количество предложений до %d и количество предложений после %d", sents_amount-1, sents_amount-1-sents_with_num);
    free_text(sentences, sents_amount);

    return 0;
}



