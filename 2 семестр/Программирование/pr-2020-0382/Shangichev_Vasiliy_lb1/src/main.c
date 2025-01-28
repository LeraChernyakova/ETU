#include <stdio.h>
#define MAX_LEN 100

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

int diff(int arr[], int size){
    int diff;
    diff = max(arr, size) - min(arr, size);
    return diff;
}

int sum(int arr[], int size){
    int minimum = min(arr, size);
    int sum = 0;
    int i;
    for (i = 0; i < size; i++){
        if (arr[i] != minimum){
            sum += arr[i];
        }
        else {
            break;
        }
    }
    return sum;
}

int main() {
    int query, size, answer;
    int values[MAX_LEN];
    char sep = ' ';
    size = 0;
    
    scanf("%d", &query);
    while (size < MAX_LEN && sep == ' '){
        scanf("%d%c", &values[size++], &sep);
    }
    
    switch (query){
        case 0:
            answer = max(values, size);
            printf("%d\n", answer);
            break;
        case 1:
            answer = min(values, size);
            printf("%d\n", answer);
            break;
        case 2:
            answer = diff(values, size);
            printf("%d\n", answer);
            break;
        case 3:
            answer = sum(values, size);
            printf("%d\n", answer);
            break;
        default:
            printf("Данные некорректны\n");
            break;
        }
	return 0;
}