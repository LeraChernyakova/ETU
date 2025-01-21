int index_first_zero(int arr[], int len){
	int n=0;
	while(n < len){
		if(arr[n] == 0)
			return n;
		n++;
	}
	return -1;
}
