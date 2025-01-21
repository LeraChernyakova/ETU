#include "abs_max.h"
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
