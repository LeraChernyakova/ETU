#include <stdio.h>
#include "sum.h"
#include "max.h"
#include "min.h"
#include "diff.h"
#define MAX_LEN 100

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