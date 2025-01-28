#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_between_even_odd(int list[], int listsize){
    int res = 0;
    
    for (int i = index_first_even(list, listsize); i < index_last_odd(list, listsize); i++){
      res += abs(list[i]);
    }
    
    return res;
}
