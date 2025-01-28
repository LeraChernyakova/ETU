//алгоритм Брезенхэма - алгоритм рисования прямых

#include <iostream>
#include <stdlib.h>
#include <cstring>
// swap for int
void swap(int& a, int& b){
    b = b ^ a;
    a = a ^ b;
    b = b ^ a;
    // write your code here...
}

// swap for char*
void swap(char*& a, char*& b){
    char * s = (char*)malloc(20*sizeof(char));
    std::strcpy(s, (const char *)a);
    std::memmove(b, a, strlen(b));
    std::memmove(s, b, strlen(a));
    // write your code here...
}

int main(){
    //int a, b;
    std::string a1, b1;
    std::cin >>a1>>b1;
    //std::cin >>a>>b;
    swap(a1,b1);
    std::cout <<"\nresult:\n"<<a1<<" "<<b1;
    return 0;

}
