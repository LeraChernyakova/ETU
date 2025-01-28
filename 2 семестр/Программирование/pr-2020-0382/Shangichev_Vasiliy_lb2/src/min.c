int min(int arr[], int size){
    int i = 0;
    int minimum;
    minimum = arr[i];

    for (i = 1; i < size; i++){
        if (arr[i] < minimum) {
            minimum = arr[i];
        }
    }
    return minimum;
}
