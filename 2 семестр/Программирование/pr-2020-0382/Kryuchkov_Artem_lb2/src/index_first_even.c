int index_first_even(int list[], int listsize){
    for (int i = 0; i < listsize; i++){
        if(list[i]%2==0) {
            return i;
        }   
    }
}