#include <stdio.h>
#include <stdlib.h>
#include "sum.h"
int sum(int arr[],int N){
	int sum=0,max=0,num;
	int i;
	for(i=0;i<N;i++){
			
		if(abs(max)<abs(arr[i])){
			max=arr[i];	
			num=i;
		}
		
	}
	for(i=num;i<N;i++){
		sum=sum + arr[i];
		
	}
	
   return sum;
	
}
