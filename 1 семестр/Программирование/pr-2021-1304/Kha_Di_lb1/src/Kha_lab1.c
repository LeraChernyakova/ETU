#include <stdio.h>
#include <stdlib.h>
#define N 20

int index_first_negative(int a[], int n)
{
    int fn = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] < 0) {
            fn = i;
            }
    }

    return fn;
}

int index_last_negative(int a[], int n)
{
    int ln = n - 1;
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            ln = i;
            }
    }

    return ln;
}

int multi_between_negative(int a[], int n)
{
    int mb = 1;
    for (int i = index_first_negative(a, n); i < index_last_negative(a, n); i++) {
        mb *= a[i];
    }

    return mb;
}


int multi_before_and_after_negative(int a[], int n)
{
    int mba = 1;
    for (int i = 0; i < index_first_negative(a, n); i++) {
        mba *= a[i];
    }
    for (int i = index_last_negative(a, n); i < n; i++) {
        mba *= a[i];
    }

    return mba;
}


int main()
{
    char s;
    int arr[N], a, k = 0;
    scanf("%d", &a);
    for (int i = 0; i < N; i++) {
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