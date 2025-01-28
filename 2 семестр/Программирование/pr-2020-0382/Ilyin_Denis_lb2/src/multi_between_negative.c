#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"

int multi_between_negative(int mass[20]){
int i, between, first, last;
between = 1;
first = index_first_negative(mass);
last = index_last_negative(mass);
for (i = first; i < last; i++) {
between = between * (mass[i]);
}
return between;
}
