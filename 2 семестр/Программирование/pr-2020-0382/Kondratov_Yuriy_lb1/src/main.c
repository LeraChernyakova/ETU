#include <stdio.h>

int max(int ar[], int len){
    int ans = ar[0];
    for (int i = 1; i < len; i++){
        if (ar[i] > ans){
           ans = ar[i];
        }
    }
    return ans;
}

int min(int ar[], int len){
    int ans = ar[0];
    for (int i = 1; i < len; i++){
        if (ar[i] < ans){
           ans = ar[i];
        }
    }
    return ans;
}

int diff(int ar[], int len){
    int ans = max(ar, len) - min(ar, len);
    return ans;
}

int sum(int ar[], int len){
    int ans = 0;
    for(int i = 0; ar[i] > min(ar, len); i++){
            ans += ar[i];
    }
    return ans;
}



int main(){
    
    int array[100], index = 0, option;
    char c = ' ';
    
    scanf("%d", &option);
    
    while(index < 100 && c == ' '){
        scanf("%d%c", &array[index++], &c);
    }
    
    switch (option){
        case 0:
            printf("%d", max(array, index));
            break;
        case 1:
            printf("%d", min(array, index));
            break;
        case 2:
            printf("%d", diff(array, index));
            break;
        case 3:
            printf("%d", sum(array, index));
            break;
        default:
            printf("Данные некорректны");
    }
    
    return 0;
}
