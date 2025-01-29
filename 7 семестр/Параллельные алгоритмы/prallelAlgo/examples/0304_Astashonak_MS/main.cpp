#include <iostream>
#include "./lab1/lab1.h"
#include "./lab2/lab2.h"

#define LAB_NUMBER 1

int main() {
    std::cout << "Hello, World!" << std::endl;

    switch (LAB_NUMBER) {
        case 1: lab1(); break;
        case 2: lab2(); break;
        default: std::cout << "Incorrect lab number" << std::endl;
    }

    return 0;
}
