int max(int arr[], int size){
    int i = 0, maximum;
    maximum = arr[i];
    
    for (i = 1; i < size; i++){
        if (arr[i] > maximum) {
            maximum = arr[i];
        }
    }
    return maximum;
}