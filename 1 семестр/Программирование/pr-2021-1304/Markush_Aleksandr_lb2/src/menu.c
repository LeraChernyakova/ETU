#include <stdio.h>  
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_before_and_after.h"
#include "sum_between.h"
#define MAX_SIZE 100



int main(){

    int act;

    scanf("%d", &act);



    char space;

    int input[MAX_SIZE];

    int size = 0;

    for(int i = 0; i < MAX_SIZE; i++){

        scanf("%d%c", &input[i], &space);

        size++;

        if(space == '\n'){

            break;
        }
    }

    int values[size];

    for(int i = 0; i < size; i++){

        values[i] = input[i];
    }
    
   

    switch ( act ){

        case 0:

            printf("%d\n", index_first_zero(values, act, size));

            break;

        case 1:

            printf("%d\n", index_last_zero(values, act, size));

            break;

        case 2:

            printf("%d\n", sum_between(values, act, size));

            break;

        case 3:

            printf("%d\n", sum_before_and_after(values, act, size));

            break;

        default:

            printf("Данные некорректны\n");

    }

    return 0;

}
