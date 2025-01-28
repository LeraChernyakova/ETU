#pragma once
#include <iostream>

class Output {
public:
    virtual ~Output()=default;
    virtual Output& operator<<(std::string message)=0;
    virtual void changeY(int a)=0;
};