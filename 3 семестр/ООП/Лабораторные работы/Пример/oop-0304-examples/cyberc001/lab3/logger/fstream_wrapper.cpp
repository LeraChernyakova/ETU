#include "fstream_wrapper.h"
#include <iostream>

fstream_wrapper::fstream_wrapper(std::ofstream& os, const char* fname) : ostream_wrapper((std::ostream&)os)
{
	this->fname = fname;
	os_open();
}

void fstream_wrapper::os_open()
{
	((std::ofstream&)os).open(fname);
}
void fstream_wrapper::os_close()
{
	((std::ofstream&)os).close();
}
