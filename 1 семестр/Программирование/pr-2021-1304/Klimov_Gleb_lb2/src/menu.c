#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
int n;
int N=100;
scanf("%d",&n);
int arr[N];
char ch;
int i=0;
for(i=0;i<N;i++){
 	arr[i]=0;
 }
 i=0;
 
 for(i=0;i<N;i++){
 	scanf("%d%c",&arr[i],&ch);
	if(ch =='\n'){
		break;
	}
 }

switch(n){
	case 0:
		printf("%d\n",index_first_even(arr));
		break;
	case 1:
		printf("%d\n",index_last_odd(arr));
		break;
	case 2:
		printf("%d\n",sum_between_even_odd(arr));
		break;
	case 3:
			printf("%d\n",sum_before_even_and_after_odd(arr));
		break;
	default:
	         printf("Данные некорректны");
}



return 0;


}
