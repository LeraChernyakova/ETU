#include <stdio.h>

#include <stdlib.h>


#define MAX_SIZE 100  


int index_first_zero(int values[], int act, int size){

    int truth = 0;
    int first = 0;

    for(int i = 0; i < size; i++){
        if(values[i] == 0){
            first = i;
            if (act == 0){
                printf("%d\n", first);
            }
            truth = 1;
            break;
        }
    }

    if(truth == 0){
        printf("Данные некорректны\n");
	exit(EXIT_SUCCESS);
    }

    return first;
}



int index_last_zero(int values[], int act, int size){

    int truth = 0;
    int last = 0;

    for(int i = (size - 1); i >= 0; i--){
        if(values[i] == 0){
            last = i;
            if(act == 1){
                printf("%d\n", last);
            }
            truth = 1;
            break;
        }
    }

    if(truth == 0){
        printf("Данные некорректны\n");
	exit(EXIT_SUCCESS);
    }

    return last;
}

int sum_between(int values[], int act, int size){

    int first = index_first_zero(values, act, size);
    int last = index_last_zero(values, act, size);
    int sum = 0;

    for(int i = first; i < last; i++){

        sum += abs(values[i]);
    }

    if(act == 2){
        printf("%d\n", sum);
    }

    return sum;
}



void sum_before_and_after(int values[], int act, int size){

    int all_sum = 0;

    for(int i = 0; i < size; i++){

        all_sum += abs(values[i]);
    }

    int sum;
    sum = all_sum - sum_between(values, act, size);
    printf("%d\n", sum);
}


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
            index_first_zero(values, act, size);
            break;

        case 1:
            index_last_zero(values, act, size);
            break;

        case 2:
            sum_between(values, act, size);
            break;

        case 3:
            sum_before_and_after(values, act, size);
            break;

        default:
            printf("Данные некорректны\n");
    }
    return 0;
}

