#include <stdio.h>
#define MAX_BUFFER 100

void printArr(int* arr, int size){
    for (int i = 0; i < size; i++){
        printf("%d", arr[i]);
    }
}

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
    printf("%c", '\n');
    printArr(arr, size);

    switch (arr[0]) {
        case 0:break;
        case 1:break;
        case 2:break;
        case 4:break;
    }
    return 0;
}
