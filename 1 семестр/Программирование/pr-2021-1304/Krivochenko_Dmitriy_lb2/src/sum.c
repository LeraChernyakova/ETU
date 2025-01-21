#include "sum.h"
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
