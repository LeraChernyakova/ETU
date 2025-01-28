#include "observer_actor.h"

#include <sstream>

void observer_actor::setActor(actor& ac)
{
	this->ac = &ac;
	ac.setObserver(*this);
}
void observer_actor::notify()
{
	actor& _ac = *ac;

	for(auto i = oslist.begin(); i != oslist.end(); ++i){
		ostream_wrapper& ow = (*i);
		std::stringstream ss;
		ss << _ac;
		ow.print(ss.str());
	}
}
