#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"


int index_first_even(int[], int);
int index_last_odd(int[], int);
int sum_between_even_odd(int[], int);
int sum_before_even_and_after_odd(int[], int);

int main(){
    int size = 0, array[100], val;
    char spaceb = ' ';

    scanf("%d", &val);

    while(size < 100 && spaceb == ' '){
        scanf("%d%c",&array[size++], &spaceb);
    }

    switch (val){
        case 0:
            printf("%d\n", index_first_even(array, size));
            break;
        case 1:
            printf("%d\n", index_last_odd(array, size));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(array, size));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(array, size));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}