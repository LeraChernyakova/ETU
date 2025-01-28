#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_before_and_after_negative(int a[], int a_size){
    int fn = index_first_negative(a, a_size);
    int ln = index_last_negative(a, a_size);
    int res1 = 1, res2 = 1, m_res = 0;
    int i;
    for(i = 0; i < fn; i++)
        res1 *= a[i];
    for(i = ln; i < a_size; i++){
        res2 *=a[i];
    }
    m_res = res1 * res2;
return m_res;
}

