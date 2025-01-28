#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

int comparator(const void *int1, const void *int2) {
    int *arr1 = (int *) int1;
    int *arr2 = (int *) int2;

    return (*arr1 - *arr2);
}

int main() {
    int num_amount = 10;
    int buf;
    int arr[num_amount];
    int arr2[num_amount];
    for (int i = 0; i < num_amount; i++) {
        scanf("%d", &arr[i]);
        arr2[i] = arr[i];
    }

    clock_t t;
    t = clock();
    for (int i = 0; i < num_amount; i++) {
        for (int j = num_amount - 1; j > i; j--)
            if (arr[j - 1] > arr[j]) {
                buf = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = buf;
            }
    }

    float time1 = ((float) t) / CLOCKS_PER_SEC;
    t = clock();
    qsort(arr2, num_amount, sizeof(int), comparator);
    float time2 = ((float) t) / CLOCKS_PER_SEC;

    for (int i = 0; i < num_amount; i++)
        printf("%d ", arr[i]);
    printf("\n%f\n", time1);

    printf("%f\n", time2);


    return 0;
}
