#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char **txt;
    char end_of_txt[] = "Dragon flew away!";
    int old_sentence_counter, new_sentence_counter, counter, i, indicator, checker, del_sentence, z;
    indicator = 1;
    char c;
    txt = malloc(sizeof(char*));
    new_sentence_counter = 0;
    old_sentence_counter = 0;

    while (indicator){

        txt = realloc(txt,sizeof(char*)*(new_sentence_counter + 2));
        txt[new_sentence_counter] = malloc(sizeof(char)*2);
        scanf("%c",&c);
        txt[new_sentence_counter][0] = c;
        txt[new_sentence_counter][1] = '\0';
        counter = 0;
        checker = 0;
        while ((c!='.') && (c!=';') && (c!='?') && (strcmp(txt[new_sentence_counter],end_of_txt))){

            counter = counter +1;
            txt[new_sentence_counter] = realloc(txt[new_sentence_counter],sizeof(char)*(counter+2));
            scanf("%c",&c);
            txt[new_sentence_counter][counter] = c;
            txt[new_sentence_counter][counter+1] = '\0';
        }
        for(i = 0; i < counter; i++){
            if (isdigit(txt[new_sentence_counter][i])){
                del_sentence = 0;
                z = i;
                if (i != 0){
                    while (del_sentence != 1){
                        if (z == 0){
                            break;
                        }
                        if (txt[new_sentence_counter][z] == ' ' || txt[new_sentence_counter][z] == '.' || txt[new_sentence_counter][z] == ';' || txt[new_sentence_counter][z] == '?' || txt[new_sentence_counter][z] == '\n'){
                            break;
                        }
                        if (isalpha(txt[new_sentence_counter][z])){
                            del_sentence = 1;
                            break;
                        }
                        z = z - 1;
                    }
                    if (del_sentence == 1){
                        z = i;
                        while (del_sentence != 2){
                            if (z == counter){
                                break;
                            }
                            if (txt[new_sentence_counter][z] == ' ' || txt[new_sentence_counter][z] == '.' || txt[new_sentence_counter][z] == ';' || txt[new_sentence_counter][z] == '?' || txt[new_sentence_counter][z] == '\n'){
                                break;
                            }
                            if (isalpha(txt[new_sentence_counter][z])){
                                del_sentence = 2;
                                checker = 1;
                                break;
                            }
                            z = z + 1;
                        }
                    }
                }
            }
        }
        scanf("%c",&c);
        if ((strcmp(txt[new_sentence_counter],end_of_txt)) == 0){
            indicator = 0;
        }

        if (checker == 1){
            free(txt[new_sentence_counter]);
            new_sentence_counter = new_sentence_counter - 1;
        }

        new_sentence_counter = new_sentence_counter + 1;
        old_sentence_counter = old_sentence_counter + 1;
    }

    for(i = 0; i < new_sentence_counter; i++){
        printf("%s\n",txt[i]);
    }

    for(i = 0; i < new_sentence_counter; i++){
        free(txt[i]);
    }

    free(txt);
    printf("Количество предложений до %d и количество предложений после %d\n",old_sentence_counter-1,new_sentence_counter-1);

    return 0;
}
