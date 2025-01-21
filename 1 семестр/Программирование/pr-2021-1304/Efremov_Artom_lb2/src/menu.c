#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
int main()
{
    int i;
    int fv, err = 0, ans = 0, counter = 0;
    int arr[20] = { 0 };
    char ch;
    scanf("%d", &fv);
    for (i = 0; i < 20; i++)
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
            printf("%d\n", ans);
        else
            printf("Данные некорректны\n");
        break;
    case 1:
        ans = index_last_negative(arr, counter);
        if (ans != -1)
            printf("%d\n", ans);
        else
            printf("Данные некорректны\n");
        break;
    case 2:
        ans = multi_between_negative(arr, counter, &err);
        if (err)
            printf("Данные некорректны\n");
        else
            printf("%d\n", ans);
        break;
    case 3:
        ans = multi_before_and_after_negative(arr, counter, &err);
        if (err)
            printf("Данные некорректны\n");
        else
            printf("%d\n", ans);
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
    return 0;
}
