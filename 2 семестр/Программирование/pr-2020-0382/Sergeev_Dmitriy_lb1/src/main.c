#include <stdio.h>
#include <stdlib.h>

int index_first_even(int A[], int b)
{
    int ind = 0;
    while ((abs(A[ind]) % 2 == 1) && (ind != b))
    {
        ind++;
    }
    return (ind);
}

int index_last_odd(int A[], int b)
{
    b = b - 1;
    while ((A[b] % 2 == 0) && (b >= 0))
    {
        b--;
    }
    return (b);
}

int sum_between_even_odd(int A[], int b)
{
    int f, l, summ = 0;
    f = index_first_even(A, b);
    l = index_last_odd(A, b);
    int i;
    for (i = f; i < l; i++)
    {
        summ = summ + abs(A[i]);
    }
    return (summ);
}

int sum_before_even_and_after_odd(int A[], int b)
{
    int summ = 0;
    int i;
    for (i = 0; i < b; i++)
    {
        summ = summ + abs(A[i]);
    }
    summ = summ - sum_between_even_odd(A, b);
    return summ;
}

int main()
{
    int k = 0;
    scanf("%d", &k);
    int arr[100];
    int arr_size = 0;
    char sym = ' ';
    while (arr_size < 100 && sym == ' ')
    {
        scanf("%i%c", &arr[arr_size++], &sym);
    }
    switch (k)
    {
    case 0:
        printf("%d\n", index_first_even(arr, arr_size));
        break;
    case 1:
        printf("%d\n", index_last_odd(arr, arr_size));
        break;
    case 2:
        printf("%d\n", sum_between_even_odd(arr, arr_size));
        break;
    case 3:
        printf("%d\n", sum_before_even_and_after_odd(arr, arr_size));
        break;
    default: printf("Данные некорретны\n"); break;
    }
    return 0;
}
