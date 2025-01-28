#include "index_first_negative.h"

int index_first_negative(int mass[20]) {
int i, first;
first = -1;
for (i = 0; i < 20; i++) {
if ((first == -1) && (mass[i] < 0) ){
first = i;
}
}
return first;
}
