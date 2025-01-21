#include <stdio.h>
#include "read_arr.h"
#include "user_choice.h"
#define N 100


int main(){
	int arr[N];
	int x;
	int n;
	scanf("%d", &x);
	n = read_arr(arr, N);
	user_choice(x, arr, n);
	return 0;
}
