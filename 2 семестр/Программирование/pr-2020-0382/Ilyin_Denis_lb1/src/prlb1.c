#include <stdio.h>

int index_first_negative(int mass[20]) {
    int index, first;
    first = -1;
    for (index = 0; index < 20; index++) {
        if ((first == -1) && (mass[index] < 0)){
            first = index;
        }
    }
    return first;
}

int index_last_negative(int mass[20]) {
    int index, last;
    last = -1;
    for (index = 19; index >= 0; index--) {
        if ((last == -1) && (mass[index] < 0)){
            last = index;
        }
    }
    return last;
}

int multi_between_negative(int mass[20]){
    int index, between, first, last;
    between = 1;
    first = index_first_negative(mass);
    last = index_last_negative(mass);
    for (index = first; index < last; index++) {
        between = between * (mass[index]);
    }
    return between;
}

int multi_before_and_after_negative(int mass[20], int length) {
    int index, before_and_after, first, last;

    before_and_after = 1;
    first = index_first_negative(mass);
    last = index_last_negative(mass);

    for (index = 0; index < first; index++) {
        before_and_after = before_and_after * (mass[index]);
    }

    for (index = last; index < length; index++) {
        before_and_after = before_and_after * (mass[index]);
    }

    return before_and_after; 
}


int main() {
    int return_command, command, length, elem;
    command = getchar();
    length = 0;
    char read = getchar();
    int mass[20] = {0};
    /*printf("%d\n", a);*/

    while (read != '\n'){
        read = getchar();

        if (read == '-'){
            while ((read != ' ') && (read != '\n')){
                if (read == '-'){
                    read = getchar();
                }
                else {
                    elem = read - '0';
                    /*printf("%d\n", mass[length]);*/
                    mass[length] = mass[length]*10 - elem;
                    /*printf("%d\n", mass[length]);*/
                    read = getchar();
                }
            }
        }
        else {
            while ((read != ' ') && (read != '\n')){
                elem = read - '0';
                /*printf("%d\n", mass[length]);*/
                mass[length] = mass[length]*10 + elem;
                /*printf("%d\n", mass[length]);*/
                read = getchar();
            }
        }
        ++length;

    }

    switch(command){
        case '0': 
            return_command = index_first_negative(mass);
            printf("%d", return_command);
            break;
        case '1': 
            return_command = index_last_negative(mass);
            printf("%d", return_command);
            break;
        case '2': 
            return_command = multi_between_negative(mass);
            printf("%d", return_command);
            break;
        case '3': 
            return_command = multi_before_and_after_negative(mass, length);
            printf("%d", return_command);
            break;
        default:
            printf ("Данные некорректны");
            break;
    }
    return 0;

}
