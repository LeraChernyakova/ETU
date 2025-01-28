#include "diff.h"
#include "max.h"
#include "min.h"

//f() разница между макс. и мин. элементами

int diff(int n, int Arr[]){
    return (Arr[max(n, Arr)]-Arr[min(n, Arr)]);
}
