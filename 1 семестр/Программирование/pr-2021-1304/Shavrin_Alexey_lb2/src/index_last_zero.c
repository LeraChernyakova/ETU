int index_last_zero(int arr[], int len){
	for(int i=len-1; i>=0; i--){
		if(arr[i] == 0)
			return i;
	}
	return -1;
}
