#include <stdlib.h>
int index_last_odd(int list[], int listsize){
    for (int i = listsize - 1; i >= 0; i--){
        if(abs(list[i])%2==1) {
            return i;
        }   
    }
}
