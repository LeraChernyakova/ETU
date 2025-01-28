#include <stdio.h>
#include <stdlib.h>

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

int index_first_even(int array[], int size){
    int counter0;
    for(counter0 = 0; counter0 <= size; counter0++)
        if(abs(array[counter0])%2 == 0)
            return counter0;
}

int index_last_odd(int array[], int size){
    int counter1;
    for(counter1 = size-1; counter1 >= 0; counter1--)
        if(abs(array[counter1])%2 == 1)
            return counter1;
}

int sum_between_even_odd(int array[], int size){
    int counter2, sbed = 0;
    for(counter2 = index_first_even(array, size); counter2 < index_last_odd(array, size); counter2++)
        sbed += abs(array[counter2]);
    return sbed;
}

int sum_before_even_and_after_odd(int array[], int size){
    int counter3, counter4, sbeaao = 0;
    for(counter3 = index_first_even(array, size) - 1;  counter3 >= 0;  counter3--)
        sbeaao += abs(array[counter3]);
    for(counter4 = index_last_odd(array, size); counter4 < size; counter4++)
        sbeaao += abs(array[counter4]);
    return sbeaao;
}