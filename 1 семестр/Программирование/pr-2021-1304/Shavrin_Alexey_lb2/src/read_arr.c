#include <stdio.h>


int read_arr(int arr[], int len){
	char c;
	int n=0;
	while(n<len){
		scanf("%d%c", &arr[n], &c);
		n++;
		if(c == '\n')
			break;
	}
	return n;
}
