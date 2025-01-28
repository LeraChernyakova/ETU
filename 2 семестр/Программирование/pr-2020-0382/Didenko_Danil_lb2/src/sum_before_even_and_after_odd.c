#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int A[],int n){
        int i = 0;
        int j = 0;
        int total_sum = 0;
        int first_even = index_first_even(A,n);
        int last_odd = index_last_odd(A,n);
        while(i<n){
                if (i == first_even){
                        while (i != last_odd){
                                i++;
                        }
                }
                total_sum += abs(A[i]);
                i++;
                }
        return total_sum;
}
