#include "abs_min.h"
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
