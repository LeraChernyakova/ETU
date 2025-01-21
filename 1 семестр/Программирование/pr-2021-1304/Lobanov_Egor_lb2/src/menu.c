#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

#define N 20

int main(){
    int arr[N], task, count = 0;
    char c;
    scanf("%d%c", &task, &c);
    for (int i = 0; c != '\n'; i++){
        scanf("%d%c", &arr[i], &c);
        count++;
    }
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