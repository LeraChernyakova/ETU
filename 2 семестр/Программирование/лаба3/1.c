#include <stdio.h>

long int recFact(int n){
    long int pr = 0;
    if (n == 1)
        return 1;
    else
        pr = n * recFact(n-1);
    return pr;
}

int main(){
    long int N;
    scanf ("%ld", &N);
    printf ("%ld", recFact(N));
    return 0;
}