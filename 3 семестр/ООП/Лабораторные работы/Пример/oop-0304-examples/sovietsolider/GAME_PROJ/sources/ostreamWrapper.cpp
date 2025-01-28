#include "../headers/ostreamWrapper.h"

#include "../headers/ostreamWrapper.h"

void OstreamWrapper::os_open() {}
void OstreamWrapper::os_close() {}

OstreamWrapper::OstreamWrapper(std::ostream& os) : os(os), os_closed(false), link_cnt(0)
{
	os_open();
}

OstreamWrapper::~OstreamWrapper()
{
	if(!os_closed)
		os_close();
}

void OstreamWrapper::link()
{
	if(os_closed)
	{
		os_open();
		os_closed = false;
	}

}

void OstreamWrapper::unlink()
{
	
	if(!os_closed)
	{
		os_close();
		os_closed = true;
	}
}

void OstreamWrapper::print(const char* message)
{ os << message << std::endl; }

void OstreamWrapper::print(const std::string& message)
{ os << message << std::endl; }
