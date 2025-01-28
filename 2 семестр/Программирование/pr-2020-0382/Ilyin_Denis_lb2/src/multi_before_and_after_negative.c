#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_before_and_after_negative.h"

int multi_before_and_after_negative(int mass[20], int length) {
int i, before_and_after, first, last;

before_and_after = 1;
first = index_first_negative(mass);
last = index_last_negative(mass);

for (i = 0; i < first; i++) {
before_and_after = before_and_after * (mass[i]);
}

for (i = last; i < length; i++) {
before_and_after = before_and_after * (mass[i]);
}

return before_and_after;
}
