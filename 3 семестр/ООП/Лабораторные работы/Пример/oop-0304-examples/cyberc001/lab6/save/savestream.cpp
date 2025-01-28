#include "savestream.h"

#include "save_exceptions.h"

#include <cstring>
#include <sstream>

void savestream::writeBytes(void* bytes, size_t count)
{
	write((const char*)bytes, count);
	if(!good())
		throw save_error_unexpected_eof(count);
}
void savestream::writeString(std::string str)
{
	write(str.c_str(), std::strlen(str.c_str()));
	put('\n');
	if(!good())
		throw save_error_unexpected_eof(1);
}

void savestream::readBytes(void* bytes, size_t count)
{
	read((char*)bytes, count);
	if(!good())
		throw save_error_unexpected_eof(count);
}
std::string savestream::readString()
{
	std::stringstream _out;
	while(1) {
		int in = get();
		if(!good())
			throw save_error_unexpected_eof(1);
		if(in == '\n')
			break;
		_out << (char)in;
	}
	return _out.str();
}
