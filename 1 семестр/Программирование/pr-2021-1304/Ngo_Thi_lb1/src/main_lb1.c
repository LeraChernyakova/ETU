#include <stdio.h>
#include <stdlib.h>
 
#define N 100

int abs_max(int arr[], int size)
{
    int max = abs(arr[0]);
    int result = arr[0];
    for(int i = 1; i < size; i++){
        if (max < abs(arr[i]))
        {
            max = abs(arr[i]);
            result = arr[i];
        }
    }
    return result;
}
 
int abs_min(int arr[], int size)
{
    int min = abs(arr[0]);
    int result = arr[0];
    for(int i = 1; i < size; i++){
       if(min > abs(arr[i]))
       {
            min = abs(arr[i]);
            result = arr[i];
       }
    }
    return result;
}
 
int diff(int arr[], int size)
{
    return(abs_max(arr, size) - abs_min(arr,size));
}
 
int sum(int arr[], int size, int max)
{
    int start = 0;
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == max)
        {
            start = 1;
        }
        if (start)
        {
            sum += arr[i];
        }
    }
    return sum;
}

int main()
{
    char c;
    int array[N];
    int choice;
    int size = 0;
    int max;
    scanf("%d\n", &choice);
    while (size <= N)
    {
        scanf("%d%c", &array[size], &c);
        size++;
        if (c == '\n')
        {
            break;
        }
        if (size < 1)
        {
            printf("Данные некорректны");
            return 0;
        }
    }
    switch (choice)
    {
    case 0:
        printf("%d\n", abs_max(array, size));
        break;
    case 1:
        printf("%d\n", abs_min(array, size));
        break;
    case 2:
        printf("%d\n", diff(array, size));
        break;
    case 3:
        max = abs_max(array, size);
        printf("%d\n", sum(array, size, max));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
 
    return 0;
}
 
