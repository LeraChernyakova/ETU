#pragma once

#include <iostream>
#include <string>

class ComandReader{
private:
	std::string comand;
public:
	std::string readComand();
	int getWidth();
	int getHeight();

};