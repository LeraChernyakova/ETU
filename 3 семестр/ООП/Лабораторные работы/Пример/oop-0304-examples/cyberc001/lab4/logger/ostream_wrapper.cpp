#include "ostream_wrapper.h"

void ostream_wrapper::os_open() {}
void ostream_wrapper::os_close() {}

ostream_wrapper::ostream_wrapper(std::ostream& os): os(os), os_closed(false), link_cnt(0)
{
	os_open();
}
ostream_wrapper::~ostream_wrapper()
{
	if(!os_closed)
		os_close();
}

void ostream_wrapper::link()
{
	if(link_cnt == 0 && os_closed){
		os_open();
		os_closed = false;
	}

	++link_cnt;
}
void ostream_wrapper::unlink()
{
	--link_cnt;

	if(link_cnt == 0 && !os_closed){
		os_close();
		os_closed = true;
	}
}

void ostream_wrapper::print(const char* message){
	os << message << std::endl;
}
void ostream_wrapper::print(const std::string& message){
	os << message << std::endl;
}
