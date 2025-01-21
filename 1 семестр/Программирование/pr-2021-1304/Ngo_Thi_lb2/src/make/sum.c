#include "sum.h"
#include "min.h"
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
