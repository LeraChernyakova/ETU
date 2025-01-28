#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER 100

char* get_sentence(){
    int symbol;
    char* sentence = (char*) malloc(BUFFER * sizeof(char));
    int len_of_sentence = 0;
    int buf = BUFFER;
    symbol = getchar();
    if ((len_of_sentence != 0 && symbol == ' ')){
            sentence[len_of_sentence] = symbol;
            len_of_sentence++;
    }else if((len_of_sentence == 0 && symbol != ' ')){
            sentence[len_of_sentence] = symbol;
            len_of_sentence++;
    }
    while (1){
            symbol = getchar();
            if (len_of_sentence != 0)
                if (symbol == ' ' && sentence[len_of_sentence - 1] == ' ')
                    continue;
            sentence[len_of_sentence] = symbol;
            len_of_sentence++;
            if (symbol == '.' || symbol == ';' || symbol == '?' || symbol == '!')
                break;
            if (len_of_sentence == buf){
                buf += BUFFER;
                sentence = (char*) realloc(sentence, buf);
            }
    }
    sentence[len_of_sentence] = '\0';
    return sentence;
}

int string_checker(char * sentence){
    int num_of_Up = 0;
    for (int i = 0; i < strlen(sentence); i++){
        if (sentence[i] >= 'A' && sentence[i] <= 'Z')
            num_of_Up++;
        if (num_of_Up > 1)
            return 0;
    }
    return 1;
}

int main()
{
    char* end_of_text = "Dragon flew away!\0";
    char* sentence = " ";
    char** output_text = (char**) malloc(BUFFER * sizeof(char*));
    int size_of_otput_text = 0, buf = BUFFER, counter_all_sentences = 0, counter_rigth_sentences = 0;
    while(1){
        sentence = get_sentence();
        counter_all_sentences++;
        if (strcmp(sentence, end_of_text) == 0)
            break;
        if(string_checker(sentence)){
            output_text[size_of_otput_text] = sentence;
            size_of_otput_text++;
            counter_rigth_sentences++;
        }
        if (size_of_otput_text == buf){
            buf += BUFFER;
            output_text = (char**) realloc(output_text, buf*sizeof(char*));
        }
    }
    for(int i = 0; i < size_of_otput_text; i++){
        puts(output_text[i]);
        free(output_text[i]);
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d", counter_all_sentences - 1, counter_rigth_sentences);
    return 0;
    free(output_text);
}