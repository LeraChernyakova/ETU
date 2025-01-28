#include <stdio.h>
#include <stdlib.h>
#define N 100

int index_first_zero(int a[], int size)
{
    int i, fz;

    for (i = 0; i < size; i++)
    {
        if (a[i] == 0)
        {
            fz = i;
            break;
        }
    }
    return fz;
}

int index_last_zero(int a[], int size)
{
    int i = 0;
    int lz;


    for (i = 0; i < size; i++)
    {
        if (a[i] == 0)
        {
            lz = i;
        }
    }
    return lz;
}

int sum_between(int a[], int size)
{
    int s = 0;
    int c = index_first_zero(a, size);
    int b = index_last_zero(a, size)+1;
    for ( int i = c; i < b; i++)
    {
        s = s + abs(a[i]);
    }
    return s;
}

int sum_before_and_after(int a[], int size)
{
    int s = 0;
    int c = index_first_zero(a, size);
    int b = index_last_zero(a, size);
    for(int i = 0; i < c; i++)
    {
        s = s + abs(a[i]);
    }
    for(int i = b; i < size; i++)
    {
        s = s + abs(a[i]);
    }
    return s;
}


int main()
{
    char space =' ';
    int a[N];
    int inp, size = 0, ot;
    scanf("%d", &inp);
    while (size<N)
    {
        scanf("%d%c", &a[size++], &space);
        if(space !=' '){break;}
    }
    switch (inp)
    {
        case 0:
            ot = index_first_zero(a, size);
            printf("%d\n", ot);
            break;
        case 1:
            ot = index_last_zero(a, size);
            printf("%d\n", ot);
            break;
        case 2:
            ot = sum_between(a, size);
            printf("%d\n", ot);
            break;
        case 3:
            ot = sum_before_and_after(a, size);
            printf("%d\n", ot);
            break;

        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}