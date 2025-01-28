#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
int sum_before_even_and_after_odd(int list[], int listsize){
    int sum = 0;

    for (int i = 0; i < listsize; i++) sum += abs(list[i]);

    return sum - sum_between_even_odd(list, listsize); 
}