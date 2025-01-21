#include <stdio.h>

int max(int array[], int index){
    int maximum = array[0];
    for (int i = 0; i < index; i++)
        if (array[i] > maximum)
        maximum = array[i];
    return maximum;
}

int min(int array[], int index){
    int minimum = 101;
    for (int i = 0; i < index; i++)
        if (array[i] <= minimum)
        minimum = array[i];
    return minimum;
}

int diff(int array[], int index){
    int difference;
    difference = max(array, index) - min(array, index);
    return difference;
}

int sum(int array[], int index){
    int summa = 0, i = 0;
    while (array[i] != min(array, index)){
        summa = summa + array[i];
        i++;
    }
    return summa;
}

int main(){
    int *arr, ind = 0, n = 0;
    char symb;
    scanf ("%d", &n);
    while (symb != '\n'){
        scanf ("%d%c", &arr[ind], &symb);
        ind++;
    }
    switch (n){
        case 0:
            printf ("%d\n", max(arr, ind));
            break;
        case 1:
            printf ("%d\n", min(arr, ind));
            break;
        case 2:
            printf ("%d\n", diff(arr, ind));
            break;
        case 3:
            printf ("%d\n", sum(arr, ind));
            break;
        default: 
            printf ("Данные некорректны\n");
            break;
    }
}
