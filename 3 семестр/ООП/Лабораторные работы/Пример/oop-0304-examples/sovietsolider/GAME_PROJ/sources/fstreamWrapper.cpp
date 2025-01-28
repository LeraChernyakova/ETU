#include "../headers/fstreamWrapper.h"
#include <iostream>

FstreamWrapper::FstreamWrapper(std::ofstream& os, const char* fname) : OstreamWrapper((std::ostream&)os)
{
	this->fname = fname;
	os_open();
}

void FstreamWrapper::os_open()
{ ((std::ofstream&)os).open(fname); }

void FstreamWrapper::os_close()
{
	((std::ofstream&)os).close();
}