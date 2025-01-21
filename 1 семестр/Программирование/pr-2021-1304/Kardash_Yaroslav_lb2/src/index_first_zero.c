#include "index_first_zero.h"
int index_first_zero(int arr[],int n){
	int index=0;
	for (int i=0;i<n;i++){
	if (arr[i]==0){
		index=i;
		break;}
	}
return index;}
