#include "index_last_zero.h"

int index_last_zero(int values[], int act, int size){  

    int zero_last = 0;  

    int last = 0;  


    for(int i = (size - 1); i >= 0; i--){  

        if(values[i] == 0){  

            last = i;  

            zero_last = 1;  

            break;  

        }  

    }  


    return last;  

}  
