#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

int main() {
int f, a, length, t;
a = getchar();
length = 0;
char k = getchar();
int mass[20] = {0};
f = -1;

while (k != '\n'){
k = getchar();

if (k == '-'){
while ((k != ' ') && (k != '\n')){
if (k == '-'){
k = getchar();
}
else {
t = k - '0';
mass[length] = mass[length]*10 - t;
k = getchar();
}
}
}
else {
while ((k != ' ') && (k != '\n')){
t = k - '0';
mass[length] = mass[length]*10 + t;
k = getchar();
}
}
++length;

}

switch(a){
case '0':
f = index_first_negative(mass);
printf("%d", f);
break;
case '1':
f = index_last_negative(mass);
printf("%d", f);
break;
case '2':
f = multi_between_negative(mass);
printf("%d", f);
break;
case '3':
f = multi_before_and_after_negative(mass, length);
printf("%d", f);
break;
default:
printf ("Данные некорректны");
break;
}
return 0;

}
