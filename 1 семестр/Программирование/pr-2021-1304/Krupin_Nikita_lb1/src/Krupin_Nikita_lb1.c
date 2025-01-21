#include <stdio.h>
#include <stdlib.h> //int abs(int);
#define LIMIT 100 //Limit of array.

int index_first_negative(int* arr, int count){
    int i;
    for (i = 0; i < count; i++)
        if (arr[i] < 0) break;
    return i;
    //If i = count, there aren't negatives.
}

int index_last_negative(int* arr, int count){
    int i;
    for (i = count-1; i >= 0; i--)
        if (arr[i] < 0) break;
    return i;
    //If i < 0, there aren't negatives.
}

int sum_between_negative(int* arr, int count){
    int sum = 0;
    for (int i = index_first_negative(arr, count); i < index_last_negative(arr, count); i++)
        sum += abs(arr[i]);
    return sum;
    //If there aren't negatives or there's only one, sum = 0.
}

int sum_before_and_after_negative(int* arr, int count){
    int sum = 0;
    for (int i = 0; i < count; i++)
        if (i < index_first_negative(arr, count) || i >= index_last_negative(arr, count))
            sum += abs(arr[i]);
    return sum;
    //If there aren't negatives or there's only one, return sum of absolute values all array elements.
}

int scan_arr(int* arr){
    int i; char gap;
    for (i = 0, gap = ' '; gap != '\n'; i++)
        scanf("%d%c", &arr[i], &gap);
    return i;
    //Return count of elements.
}

void print_err(){
    printf("Данные некорректны\n");
    //Universal error message.
}

int main(){
    //Scan type of task and array of int.
    int type; scanf("%d\n", &type);
    int arr[LIMIT]; int count = scan_arr(arr);
    
    //Print result of current task.
    switch (type){
        case 0:
            if (index_first_negative(arr, count) < count)
                printf("%d\n", index_first_negative(arr, count));
            else print_err();
            break;
        case 1:
            if (index_last_negative(arr, count) >= 0)
                printf("%d\n", index_last_negative(arr, count));
            else print_err();
            break;
        case 2:
            printf("%d\n", sum_between_negative(arr, count));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_negative(arr, count));
            break;
        default:
            print_err();
    }
    
    return 0;
}
