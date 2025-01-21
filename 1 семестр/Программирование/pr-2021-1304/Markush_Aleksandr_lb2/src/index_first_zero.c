#include "index_first_zero.h"


int index_first_zero(int values[], int act, int size){  

    int zero_first = 0;  

    int first = 0;  


    for(int i = 0; i < size; i++){  

        if(values[i] == 0){  

            first = i;  

            zero_first = 1;  

            break;  

        }  

    }  


    return first;   

}  
