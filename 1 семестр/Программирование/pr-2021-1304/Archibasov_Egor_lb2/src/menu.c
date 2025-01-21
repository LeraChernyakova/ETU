#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

#define N 20

int main(){
	int a, len, Arr[N];
	char n;

        scanf("%d\n", &a);
        for(int i = 0; i < N; i++){
		scanf("%d%c", &Arr[i], &n);
		if(n == '\n'){
			len = i + 1;
			break;
		}
	}
	switch(a){
		case(0):
			printf("%d\n", index_first_negative(Arr, len));
			break;
		case(1):
			printf("%d\n", index_last_negative(Arr, len));
			break;
		case(2):
			printf("%d\n", multi_between_negative(Arr, len));
			break;
		case(3):
			printf("%d\n", multi_before_and_after_negative(Arr, len));
			break;
		default:
			puts("Данные некорректны\n");
	}
}
