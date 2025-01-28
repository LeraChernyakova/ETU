#include "observer.h"

observer::observer(ostream_wrapper& os)
{
	this->oslist.push_back(os);
	os.link();
}
observer::observer(const std::vector<std::reference_wrapper<ostream_wrapper>>& streams)
{
	for(auto i = streams.begin(); i != streams.end(); ++i){
		ostream_wrapper& ow = (*i);
		ow.link();
		oslist.push_back(*i);
	}
}
observer::~observer()
{
	for(auto i = oslist.begin(); i != oslist.end(); ++i){
		ostream_wrapper& ow = (*i);
		ow.unlink();
	}
}
