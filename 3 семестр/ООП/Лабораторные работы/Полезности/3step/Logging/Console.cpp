#include "Console.h"

Console::Console(int y){
    x=0;
    this->y=y+10;
};
Output& Console::operator<<(std::string message){
    cons.gotoxy(x,y);
    y+=1;
    std::cout<<message<<'\n';
    return *this;
};

void Console::changeY(int a){
    y=a+10;
};
