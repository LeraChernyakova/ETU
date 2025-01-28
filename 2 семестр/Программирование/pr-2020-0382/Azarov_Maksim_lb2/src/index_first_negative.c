int idx_frst_otr(int arr[],int len){
	int i, bol = 0,res;

	for (i = 0; (i < len)&&(bol == 0);++i)
		if (arr[i] < 0){
			res = i;
			bol = 1; 
		}	
	if (bol == 1) return res;
	else return -1;
        

}	
