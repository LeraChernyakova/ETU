#include <stdio.h>

#define N 20

int read_arr(int arr[], int length){
    char c;
    int count;
    for (int i = 0; i < length; ++i){
        scanf("%d%c", &arr[i], &c);
        count++;
        if (c == '\n'){
            break;
        }
    }
    return count;
}

int index_first_negative(int arr[], int count){
    int indx;
    for (int i = 0; i < count; ++i){
        if (arr[i] < 0){
            indx = i;
            break;
        }
    }
    return indx;
}

int index_last_negative(int arr[], int count){
    int indx;
    for (int i = count - 1; i >= 0; --i){
        if (arr[i] < 0){
            indx = i;
            break;
        }
    }
    return indx;
}

int multi_between_negative(int arr[], int count){
    int result = 1, first_negative = index_first_negative(arr, count), last_negative = index_last_negative(arr, count);
    for(int i = first_negative; i < last_negative; ++i){
        result *= arr[i];
    }
    return result;
}

int multi_before_and_after_negative(int arr[], int count){
    int result = 1, first_negative = index_first_negative(arr, count), last_negative = index_last_negative(arr, count);
    for(int i = 0; i < first_negative; ++i){
        result *= arr[i];
    }
    for(int i = last_negative; i < count; ++i){
        result *= arr[i];
    }
    return result;
}

int main(){
    int arr[N], task, count = 0;
    char c;
    scanf("%d%c", &task, &c);
    count = read_arr(arr, N);
    switch (task) {
        case 0:
            printf("%d\n", index_first_negative(arr, count));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr, count));
            break;
        case 2:
            printf("%d\n", multi_between_negative(arr, count));
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(arr, count));
            break;
        default:
            puts("Данные некорректны");
    }
    return 0;
}