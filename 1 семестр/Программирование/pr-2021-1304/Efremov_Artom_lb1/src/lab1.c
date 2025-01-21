#include <stdio.h>
int index_first_negative(int arr[], int N)
{
    for (int i = 0; i < N; i++)
        if (arr[i] < 0)
            return i;
    return -1;
}
int index_last_negative(int arr[], int N)
{
    int index_l = -1;
    for (int i = 0; i < N; i++)
        if (arr[i] < 0)
            index_l = i;
    return index_l;
}
int multi_between_negative(int arr[], int N, int *err)
{
    int res = 1;
    int index_f = index_first_negative(arr, N);
    int index_l = index_last_negative(arr, N);
    if ((index_f == index_l) || (index_f < 0) || (index_l < 0))
    {
        *err = 1;
        return 0;
    }
    for (int i = index_f; i < index_l; i++)
        res *= arr[i];
    return res;
}
int multi_before_and_after_negative(int arr[], int N, int *err)
{
    int res = 1;
    int index_f = index_first_negative(arr, N);
    int index_l = index_last_negative(arr, N);
    if ((index_f == index_l) || (index_f < 0) || (index_l < 0))
    {
        *err = 1;
        return 0;
    }
    for (int i = 0; i < index_f; i++)
        res *= arr[i];
    for (int i = index_l; i < N; i++)
        res *= arr[i];
    return res;
}
int main()
{
    int fv, err = 0, ans = 0, counter = 0;
    int arr[20] = { 0 };
    char ch;
    scanf("%d", &fv);
    for (int i = 0; i < 20; i++)
    {
        scanf("%d%c", &arr[i], &ch);
        counter++;
        if (ch == '\n')
            break;
    }
    switch (fv)
    {
    case 0:
        ans = index_first_negative(arr, counter);
        if (ans != -1)
            printf("%d", ans);
        else
            printf("Данные некорректны");
        break;
    case 1:
        ans = index_last_negative(arr, counter);
        if (ans != -1)
            printf("%d", ans);
        else
            printf("Данные некорректны");
        break;
    case 2:
        ans = multi_between_negative(arr, counter, &err);
        if (err)
            printf("Данные некорректны");
        else
            printf("%d", ans);
        break;
    case 3:
        ans = multi_before_and_after_negative(arr, counter, &err);
        if (err)
            printf("Данные некорректны");
        else
            printf("%d", ans);
        break;
    default:
        printf("Данные некорректны");
        break;
    }
}
