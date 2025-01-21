#include "size_of_massive.h"
#include <stdio.h>
#include <stdlib.h>
int size_of_massive(int arr[100], int n){
    int i;
    char c;
    for (i = 0; i < n; i++){
        scanf("%d%c", &arr[i], &c);
        if (c == '\n'){
            break;
        }
    }
    return i+1;
}
