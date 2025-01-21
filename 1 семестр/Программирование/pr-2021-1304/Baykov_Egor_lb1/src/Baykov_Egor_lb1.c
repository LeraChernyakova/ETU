#include <stdio.h>

int max(int array[], int len);
int min(int array[], int len);
int diff(int array[], int len);
int sum(int array[], int len);

int main(){
    int command, array[100], len = 0;
    char sign;
    scanf("%d%c", &command, &sign);
    for (int i = 0; i < 100; i++){
        scanf("%d%c", &array[i], &sign);
        len += 1;
        if(sign == '\n'){
            break;
        }
    }
    int realArray[len];
    for (int i = 0; i < len; i++){
        realArray[i] = array[i];
    }
    switch(command){
        case 0:
            printf("\n%d", max(realArray, len));
            break;
        case 1:
            printf("\n%d", min(realArray, len));
            break;
        case 2:
            printf("\n%d", diff(realArray, len));
            break;
        case 3:
            printf("\n%d", sum(realArray, len));
            break;
        default:
            printf("\nДанные некорректны");
    }
    return 0;
}

int max(int array[], int len){
    int maximum = array[0];
    for (int i = 1; i < len; i++){
        if (array[i] > maximum){
            maximum = array[i];
        }
    }
    return maximum;
}

int min(int array[], int len){
    int minimum = array[0];
    for (int i = 1; i < len; i++){
        if (array[i] < minimum){
            minimum = array[i];
        }
    }
    return minimum;
}

int diff(int array[], int len){
    int minimum, maximum, difference;
    minimum = min(array, len);
    maximum = max(array, len);
    difference = maximum - minimum;
    return difference;
}

int sum(int array[], int len){
    int minimum = min(array, len);
    int total = 0;
    for (int i = 0; i < len; i++){
        if (array[i] != minimum){
            total += array[i];
        }
        else{
            break;
        }
    }
    return total;
}

