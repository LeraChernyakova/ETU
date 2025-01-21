#include "min.h"

int min(int *arr, int n) {

        int i;
        int mininarr = arr[1];
        for(i = 1; i < n; i++) {
           if (arr[i] <= mininarr) {
              mininarr = arr[i];
           }
	    }
	return mininarr;

}
