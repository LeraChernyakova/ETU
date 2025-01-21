int max_num(int arr[], int n){ 	
	int max = arr[1];
	for(int i=1;i < n;i++){
        if(arr[i]>=max){
        max = arr[i];
        }
	}
	return max; 
}
