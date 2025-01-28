#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_between_negative(int a[], int a_size){
    int fn = index_first_negative(a, a_size);
    int ln = index_last_negative(a, a_size);
    int res = 1;
    int i;
    for (i = fn; i < ln; i++)
        res *= a[i];
return res;
}
