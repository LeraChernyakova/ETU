#ifndef SAVESTREAM_H
#define SAVESTREAM_H

#include <fstream>
#include <cstdlib>

class savestream : public std::fstream
{
	public:

	void writeBytes(void* bytes, size_t count);
	void writeString(std::string str);

	void readBytes(void* bytes, size_t count);
	std::string readString();
};

#endif
