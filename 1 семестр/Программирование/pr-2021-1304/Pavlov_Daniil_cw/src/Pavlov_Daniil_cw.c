#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_string_correct(char* substance, int option)
{
    if (option == 1) {
        int i = 0;
        int flag = 1;
        while (substance[i] != '\0') {
            if (!((isupper(substance[i])) && !(isupper(substance[i + 1])) ||
                  (!(isupper(substance[i])) && (isupper(substance[i - 1])) && (i != 0)) ||
                  (isupper(substance[i]) && isupper(substance[i+1])))) {
                flag = 0;
                break;
            }
            i++;
        }

        if (flag == 1) {
            return 1;
        } else {
            return 0;
        }


    }else if (option == 2){         // 2nd option
        int i = 0;
        int flag = 1;
        while (substance[i] != '\0') {
            if (!(((isupper(substance[i])) && !(isupper(substance[i + 1])) ||
                   (!(isupper(substance[i])) && (isupper(substance[i - 1])) && (i != 0)) ||
                   (isupper(substance[i]) && isupper(substance[i+1]))) || (isdigit(substance[i]) )
                   && !(isdigit(substance[0])) )  ) {
                flag = 0;
                break;
            }
            i++;
        }
        if (flag == 1) {
            return 1;
        } else {
            return 0;
        }



    }

}

char* read_substance()
{
    int size = 30;
    char *sub = malloc(sizeof(char)*size);
    char* temp;
    int i = 0;
    char symbol;
    scanf(" ");

    do{
        symbol = getchar();
        if (symbol == '\n'){
            //sub[i] = '\0';
            break;

        }

        sub[i] = symbol;
        i++;

        if (i == size){
            size += 5;
            temp = realloc(sub, sizeof(char)*size);
            if (temp != NULL){
                sub = temp;
            }else{
                free(sub);
                return NULL;
            }


        }

    }while (1);
    sub[i] = '\0';

    return  sub;
}





char* first_task_cut(char* sub)
{
    if (is_string_correct(sub, 1) == 1) {
        char **new_sub = NULL;
        int i = 0;
        int j = 0;
        while (1) {
            new_sub = realloc(new_sub, sizeof(char *) * (i + 1));
            new_sub[i] = NULL;
            new_sub[i] = realloc(new_sub[i], sizeof(char));
            new_sub[i][0] = sub[j];
            j++;
            if (sub[j] == '\0') {
                i++;
                new_sub = realloc(new_sub, sizeof(char*) * (i + 1));
                new_sub[i] = malloc(sizeof(char)*3);
                sprintf(new_sub[i], "%s", "!!!");
                break;
            } else if ( !( isupper(sub[j]) ) ) {
                new_sub[i] = realloc(new_sub[i], sizeof(char) * 3);
                new_sub[i][1] = sub[j];
                new_sub[i][2] = '\0';
                j++;
            } else {
                new_sub[i] = realloc(new_sub[i], sizeof(char) * 2);
                new_sub[i][1] = '\0';
            }
            i++;


        }


        //* * * * * * * * * * * * * * * * * * * * * * * * * * * * *


        char *result = malloc(sizeof(char) * 300);
        char *tmp = malloc(sizeof(char));
        int n = 0;
        while (strcmp(new_sub[n], "!!!") != 0) {

            int counter = 1;
            int m = n + 1;
            while (strcmp(new_sub[n], new_sub[m]) == 0) {
                counter++;
                m++;
            }

            if (counter != 1) {
                sprintf(tmp, "%s%d", new_sub[n], counter);
                strcat(result, tmp);
                n = m;
                continue;
            } else {
                sprintf(tmp, "%s", new_sub[n]);
                strcat(result, tmp);
            }


            n++;
        }


        return result;
    }else{
        return NULL;
    }
}




char* second_task_uncover(char* sub)
{
    if (is_string_correct(sub, 2) == 1) {
        int size_of_result = 200;
        char* result = malloc(sizeof(char)*size_of_result);
        char* tmp = malloc(sizeof(char)*50);
        int i = 0;
        int j;
        while (i < strlen(sub) ) {


            if (isupper(sub[i]) && islower(sub[i+1])){
                int flag_one = 1;
                j = i+2;
                char* number_str = malloc(sizeof(char)*4);

                if (isdigit(sub[j])){
                    strcat(number_str, &sub[j]);
                    flag_one = 0;
                }

                if (flag_one == 0) {
                    int number_int = atoi(number_str);
                    for (int n = 0; n < number_int; n++) {//||||||||
                        if (strlen(result) >= size_of_result){
                            size_of_result += 200;
                            result = realloc(result, sizeof(char)*size_of_result);
                        }
                        sprintf(tmp, "%c%c", sub[i], sub[i+1]);
                        strcat(result, tmp);
                    }
                }else{//||||||||||||||||||||||||||||||||||||||||||||||
                    if (strlen(result) >= size_of_result){
                        size_of_result += 200;
                        result = realloc(result, sizeof(char)*size_of_result);
                    }
                    sprintf(tmp, "%c%c", sub[i], sub[i+1]);
                    strcat(result, tmp);

                }//||||||||||||||||||||||||||||||||||||||||||||||||||||


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            }else if (isupper(sub[i]) && !(islower(sub[i+1]))){
                int flag_two = 1;
                j = i+1;
                char* number_str = malloc(sizeof(char)*4);

                if (isdigit(sub[j])){
                    strcat(number_str, &sub[j]);
                    flag_two = 0;
                }

                if (flag_two == 0){
                    int number_int = atoi(number_str);
                    for (int n = 0; n < number_int; n++){//******

                        if (strlen(result) >= size_of_result){
                            size_of_result += 200;
                            result = realloc(result, sizeof(char)*size_of_result);
                        }

                        sprintf(tmp, "%c", sub[i]);
                        strcat(result, tmp);
                    }//******************************************
            }else if (!(isdigit(sub[i]))){//^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*

                    if (strlen(result) >= size_of_result){
                        size_of_result += 200;
                        result = realloc(result, sizeof(char)*size_of_result);
                    }

                    sprintf(tmp, "%c", sub[i]);
                    strcat(result, tmp);
                }

            }//^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*

            if (strlen(result) >= size_of_result){
                size_of_result += 200;
                result = realloc(result, sizeof(char)*size_of_result);
            }
            i++;


        }

        //* * * * * * * * * * * * * * * * * * * * * * * * * * * * *


        return result;
    }else{
        return NULL;
    }
}




void third_task_if_substances_are_equal(char* cut_sub, char* uncover_sub)
{
    char* cut_uncover_sub = second_task_uncover(uncover_sub);

    if (is_string_correct(cut_sub, 1) && is_string_correct(uncover_sub, 2)) {


        if (strcmp(cut_sub, cut_uncover_sub) == 0) {
            puts("[+]The substances are equal!\n");
        } else {
            puts("[-]The substances are NOT equal!\n");
        }
    }else {
        puts("[ERROR] Wrong input!\n");
    }
    free(cut_sub);
    free(cut_uncover_sub);
    free(uncover_sub);


}




int main()
{

    char* substance_cut;
    char* substance_uncover;
    char* result ;


    char answer;
    int flag = 0;
    while (flag != 1) {
        printf("Chose any function:\n");
        printf("type [1] if you want to CUT your substance\n");
        printf("type [2] if you want to UNCOVER your substance\n");
        printf("type [3] if you want to CHECK If Your Cut Substance & Uncover Substance Are Equal\n");
        printf("type [4] if you want to finish the programm\n");
        scanf(" ");
        scanf("%c", &answer);
        switch (answer) {
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            case '1':
                printf("Type the substance you want to CUT\n");
                substance_cut = read_substance();
                if (substance_cut == NULL) {
                    printf("[ERROR]Memory Cannot be Allocated!\n");
                    break;
                }
                printf("Your substance is  %s!\n", substance_cut);

                result = first_task_cut(substance_cut);

                if (result != NULL) {
                    printf("\nYour Cutten Substance is: ");
                    puts(result);
                } else {
                    printf("[ERROR]The Substance is INCORRECT!\n");
                    break;
                }
                free(substance_cut);
                free(result);
                break;
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            case '2':
                printf("Type the substance you want to UNCOVER\n");
                substance_uncover = read_substance();
                if (substance_uncover == NULL) {
                    printf("[ERROR]Memory Cannot be Allocated!\n");
                    break;
                }
                printf("Your substance is  %s!\n", substance_uncover);

                result = second_task_uncover(substance_uncover);
                if (result != NULL) {
                    printf("\nYour Uncovered Substance is: ");
                    puts(result);
                } else {
                    printf("[ERROR]The Substance is INCORRECT!\n");
                    break;
                }

                free(substance_uncover);
                free(result);
                break;
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            case '3':
                printf("Type the substance you want number 1\n");
                substance_cut = read_substance();
                if (substance_cut == NULL) {
                    printf("[ERROR]Memory Cannot be Allocated!\n");
                    break;
                }
                printf("Type the substance you want number 2\n");
                substance_uncover = read_substance();
                if (substance_uncover == NULL) {
                    printf("Memory Cannot be Allocated!\n");
                    break;
                }
                printf("[1]Your substance number one is  %s!\n", substance_cut);
                printf("[2]Your substance number two is  %s!\n", substance_uncover);

                third_task_if_substances_are_equal(substance_cut, substance_uncover);

                break;
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            case '4':
                flag = 1;
                break;
            default:
                printf("[ERROR]Wrong answer!\n");
                break;

        }
    }

    return 0;
}
