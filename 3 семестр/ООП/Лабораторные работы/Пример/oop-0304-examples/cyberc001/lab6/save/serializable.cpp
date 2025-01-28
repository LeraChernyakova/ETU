#include "serializable.h"

std::string serializable::getClassName() { return "serializable"; }
void serializable::saveToFile(savestream& svs)
{
	svs.writeString(getClassName());
}
void serializable::loadFromFile(savestream& svs)
{
	std::string name = svs.readString();
}
