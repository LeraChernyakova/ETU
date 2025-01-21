#include <stdio.h>
#include <stdlib.h>


int abs_max(int arr[], int k);
int abs_min(int arr[], int k);
int diff(int arr[], int k);
int sum(int arr[], int k, int mx_abs);

int main()
{
    char inp;
    int arr[101];
    int command;
    int count = 0;
    int mx, mn, df, sm;

    scanf("%d\n", &command);
    while (count <= 101)
    {
        scanf("%d%c", &arr[count], &inp);
        count++;
        if (inp == '\n')
        {
            break;
        }
        if (count > 100)
        {
            printf("Данные некорректны");
            return 0;
        }
    }

    mx = abs_max(arr, count);
    mn = abs_min(arr, count);
    df = diff(arr, count);
    sm = sum(arr, count, mx);

    switch (command)
    {
        case 0:
            printf("%d\n", mx);
            break;
        case 1:
            printf("%d\n", mn);
            break;
        case 2:
            printf("%d\n", df);
            break;
        case 3:
            printf("%d\n", sm);
            break;
        default:
            puts("Данные некорректны");
    }

    return 0;
}

int abs_max(int arr[], int k)
{
    int max_abs = 0;
    int max;
    for (int i = 0; i < k; i++)
    {
        if (abs(arr[i]) > max_abs)
        {
            max_abs = abs(arr[i]);
            max = arr[i];
        }
    }
    return max;
}

int abs_min(int arr[], int k)
{
    int min_abs = 10000;
    int min;
    for (int i = 0; i < k; i++)
    {
        if (abs(arr[i]) < min_abs)
        {
            min_abs = abs(arr[i]);
            min = arr[i];
        }
    }
    return min;
}

int diff(int arr[], int k)
{
    int max = abs_max(arr, k);
    int min = abs_min(arr, k);
    return (max - min);
}

int sum(int arr[], int k, int mx_abs)
{
    int ind = 0;
    int sm = 0;
    for (int i = 0; i < k; i++)
    {
        if (arr[i] == mx_abs)
        {
            ind = 1;
        }
        if (ind)
        {
            sm = sm + arr[i];
        }
    }
    return sm;
}
