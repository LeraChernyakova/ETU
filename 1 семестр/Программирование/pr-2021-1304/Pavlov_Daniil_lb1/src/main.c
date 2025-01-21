#include <stdio.h>
#define MAX_BUFFER 101

// **********************OPTION DEFS********************************************

int min(int array[], int I){        // I == size of array
    int minimum = 100000;
    for (int i = 1;i < I; i++){         // int i = 1 because arr[0] == option
        if (minimum > array[i]){
            minimum = array[i];
        }
    }
    return minimum;
}



int max(int array[], int I){
    int maximum = 0;
    for (int i = 1;i < I; i++){
        if (maximum < array[i]){
            maximum = array[i];
        }
    }
    return maximum;
}



int diff(int array[], int I){
    int difference, maximum, minimum;
    maximum = max(array, I);
    minimum = min(array, I);
    difference = maximum - minimum;
    return difference;
}



int sum(int array[], int I){
     int minimum = min(array, I);
     int total = 0;
     for (int i = 1; i < I; i++){
         if (array[i] != minimum){
             total += array[i];
         }
         else{
             break;
         }
     }
     return total;
}

//******************************************************************************

int main(){
    int arr[MAX_BUFFER];
    char c;
    int size = 0;
    for(int i = 0; i < MAX_BUFFER; i++){
        scanf("%d%c", &arr[i], &c);
        size++;
        if (c == '\n'){
            break;
        }
        
    }


    
    switch (arr[0]) {
        case 0:
            printf("\n%d", max(arr, size));
            break;
        case 1:
            printf("\n%d", min(arr, size));
            break;
        case 2:
            printf("\n%d", diff(arr, size));
            break;
        case 3:
            printf("\n%d", sum(arr, size));
            break;
        default:
            printf("\nДанные некорректны");
    }
    return 0;
}

