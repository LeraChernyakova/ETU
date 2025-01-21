#include <stdio.h>
#include <stdlib.h>

#define N 101

int abs_max(int list[], int k);            //max по модулю
int abs_min(int list[], int k);            //min по модулю
int diff(int list[], int k);               //разница между max и min
int sum(int list[], int k, int start_num); //сумма элементов, начина с max по модулю

int main()
{
    char c;
    int arr[N];
    int usr;
    int count = 0;
    int answ0, answ1, answ2, answ3;

    scanf("%d\n", &usr);
    while (count <= N)
    {
        scanf("%d%c", &arr[count], &c);
        count++;
        if (c == '\n')
        {
            break;
        }
        if (count > (N - 1))
        {
            printf("Данные некорректны");
            return 0;
        }
    }

    answ0 = abs_max(arr, count);
    answ1 = abs_min(arr, count);
    answ2 = diff(arr, count);
    answ3 = sum(arr, count, answ0);

    switch (usr)
    {
    case 0:
        printf("%d\n", answ0);
        break;
    case 1:
        printf("%d\n", answ1);
        break;
    case 2:
        printf("%d\n", answ2);
        break;
    case 3:
        printf("%d\n", answ3);
        break;
    default:
        puts("Данные некорректны");
    }

    return 0;
}

int abs_max(int list[], int k)
{
    int max_num = 0;
    int answ;
    for (int i = 0; i < k; i++)
    {
        if (abs(list[i]) > max_num)
        {
            max_num = abs(list[i]);
            answ = list[i];
        }
    }
    return answ;
}

int abs_min(int list[], int k)
{
    int min_num = 10000;
    int answ;
    for (int i = 0; i < k; i++)
    {
        if (abs(list[i]) < min_num)
        {
            min_num = abs(list[i]);
            answ = list[i];
        }
    }
    return answ;
}

int diff(int list[], int k)
{
    int ma = abs_max(list, k);
    int mi = abs_min(list, k);
    return (ma - mi);
}

int sum(int list[], int k, int start_num)
{
    int tumblr = 0;
    int curr_sum = 0;
    for (int i = 0; i < k; i++)
    {
        if (list[i] == start_num)
        {
            tumblr = 1;
        }
        if (tumblr)
        {
            curr_sum = curr_sum + list[i];
        }
    }
    return curr_sum;
}