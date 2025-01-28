#include <stdio.h>
#include <stdlib.h>
 
int index_first_zero(int arr[], int n)
{
    int index, index_first = -1;
    for (index = 0; index < n; index ++) 
    {
        if (arr[index] == 0 && index_first == -1)
            index_first = index;
    }
    return index_first;
}
int index_last_zero(int arr[], int n)
{
    int index, index_last = 100;
    for (index = 0; index < n; index ++) 
    {
        if (arr[index] == 0)
            index_last = index;
    }
    return index_last;
} 
 
int sum_between(int arr[], int n)
{
    int ind_first, ind_last, sum = 0, item;
    ind_first = index_first_zero(arr, n);
    ind_last = index_last_zero(arr, n);
    if (ind_first == -1 && ind_last == 100)
        return -1;
    for (item = ind_first; item <= ind_last; item ++)
        sum = sum + abs(arr[item]);
    return sum;
}

int sum_before_and_after(int arr[], int n)
{
    int ind_first, ind_last, sum = 0, item;
    ind_first = index_first_zero(arr, n);
    ind_last = index_last_zero(arr, n);
    if (ind_first == -1 && ind_last == 100) 
        return -1;
    for (item = 0; item <= ind_first; item ++)
    {
        sum = sum + abs(arr[item]);
    }
    for (item = ind_last; item < n; item ++)
        sum = sum + abs(arr[item]);
    return sum;    
}

int main()
{
    int a, arr[100], arr_size, res;
    char sym = ' ';
    scanf("%d", &a);
    for (arr_size = 0; arr_size < 100 && sym == ' '; arr_size ++)
    {
         scanf("%d%c", &arr[arr_size], &sym);
    }
    switch (a)
    {case 0:
        res = index_first_zero(arr, arr_size);
        if (res != -1)
            printf("%d\n", res);
        else
            printf("Данные некорректны\n");
        break;
     case 1:
        res = index_last_zero(arr, arr_size);
        if (res != 100)
            printf("%d\n", res);
        else
            printf("Данные некорректны\n");
        break;
     case 2: 
        res = sum_between(arr, arr_size);
        if (res != -1)
            printf("%d\n", res);
        else
            printf("Данные некорректны\n");
        break;
     case 3:
        res = sum_before_and_after(arr, arr_size);
        if (res != -1)
            printf("%d\n", res);
        else
            printf("Данные некорректны\n");
        break;
     default:
         printf("Данные некорректны\n");
     }
    return 0;   
}
