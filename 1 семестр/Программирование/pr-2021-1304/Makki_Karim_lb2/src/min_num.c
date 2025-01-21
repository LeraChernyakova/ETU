int min_num(int arr[], int n){	
	int min = arr[1];
	for(int i=1;i < n;i++){
        if(arr[i]<=min){
        min = arr[i];
        }
	}
	return min; 
}
