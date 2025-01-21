#include <stdio.h>
#include <stdlib.h>
#include "sum.h"
int sum(int arr[], int k){
	int su = 0, mx = 0, number;
	int i;
	for(i = 0; i < k; i++){
		if(abs(mx) < abs(arr[i])){
			mx = arr[i];	
			number = i;
		}
	}
	for(i = number; i < k; i++){
		su = su + arr[i];
	}
   return su;
}

