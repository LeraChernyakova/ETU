#include <stdio.h>
#include "multi_before_and_after_negative.h"
#include "multi_between_negative.h"
#include "index_last_negative.h"
#include "index_first_negative.h"

#define N 20

int main()
{
    char s;
    int arr[N], a, k = 0, i;
    scanf("%d", &a);
    for (i = 0; i < N; i++) {
        scanf("%d%c", &arr[i], &s);
        k++;
        if (s == '\n')
            break;
    }
        
    switch (a) {
        case 0:
            printf("%d\n", index_first_negative(arr, k));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr, k));
            break;
        case 2:
               printf("%d\n", multi_between_negative(arr, k));
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(arr, k));
            break;
        default:
            puts("Данные некорректны\n");
    }
    return 0;
}