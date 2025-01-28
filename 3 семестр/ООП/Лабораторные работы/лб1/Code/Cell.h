#pragma once
#include "Position.h"
#include <string>

class Cell{
private:
	std::string type;
	bool patency;
public:
	Cell();
	Cell(bool patency, std::string type);
	Cell(const Cell& obj);
	Cell& operator=(const Cell& obj) {
		if (this != &obj) {
			type = obj.type;
			patency = obj.patency;
		}
		return *this;
	}

	Cell(const Cell& obj, const Cell& obj2);

	void setType(std::string type_);
	std::string getType();

	void setPatency(bool patency_);
	bool getPatency();

	bool isPlayerHere();
};