#include "diff.h"
#include "abs_max.h"
#include "abs_min.h"
int diff(int list[], int k)
{
    int ma = abs_max(list, k);
    int mi = abs_min(list, k);
    return (ma - mi);
}
