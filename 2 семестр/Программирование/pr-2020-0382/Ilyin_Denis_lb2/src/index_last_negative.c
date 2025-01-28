#include "index_last_negative.h"

int index_last_negative(int mass[20]) {
int i, last;
last = -1;
for (i = 19; i >= 0; i--) {
if ((last == -1) && (mass[i] < 0) ){
last = i;
}
}
return last;
}
