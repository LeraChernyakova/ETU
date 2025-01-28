#include "ComandReader.h"

std::string ComandReader::readComand() {
	std::cin >> comand;
	return comand;
}
int ComandReader::getWidth() {
	int width_;
	std::cin >> width_;
	return width_;
}

int ComandReader::getHeight() {
	int height_;
	std::cin >> height_;
	return height_;
}