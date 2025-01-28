
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ArraySize 1000




int CompareInts(const void* A, const void* B)
{
    return *(int*)A - *(int*)B;
}

void BubbleSort(int* Arr, int ArrSize)
{
    int TmpMinElemIndex;
    int TmpVal;

    for(int i = 0; i < ArrSize; ++i)
    {
        TmpMinElemIndex = i;

        for(int j = i + 1; j < ArrSize; ++j)
        {
            if(Arr[j] < Arr[TmpMinElemIndex])
            {
                TmpMinElemIndex = j;
            }
        }

        TmpVal = Arr[i];
        Arr[i] = Arr[TmpMinElemIndex];
        Arr[TmpMinElemIndex] = TmpVal;
    }
}



int main()
{
    int Arr1[ArraySize];
    int Arr2[ArraySize];
    clock_t start, stop;


    for(int i = 0; i < ArraySize; ++i)
    {
        scanf("%i", Arr1 + i);
        Arr2[i] = Arr1[i];
    }


    start = clock();
    BubbleSort(Arr1, ArraySize);
    stop = clock();

    double TimeForBubbleSort = (double)(stop - start) / CLOCKS_PER_SEC;


    start = clock();
    qsort(Arr2, ArraySize, sizeof(int), CompareInts);
    stop = clock();

    double TimeForQuickSort = (double)(stop - start) / CLOCKS_PER_SEC;



    for(int i = 0; i < ArraySize; ++i)
    {
        printf("%i ", Arr1[i]);
    }
    printf("\n");

    printf("%lf\n", TimeForBubbleSort);
    printf("%lf", TimeForQuickSort);


    return 0;
}
