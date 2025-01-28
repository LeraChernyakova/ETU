#include "global_logger.h"

std::vector<global_logger*> global_logger::loggers;

global_logger::global_logger(ostream_wrapper& os) : os(os){}


void global_logger::init_loggers(const std::vector<std::reference_wrapper<ostream_wrapper>>& streams)
{
	for(auto i = streams.begin(); i != streams.end(); ++i){
		ostream_wrapper& os = (*i).get();
		loggers.push_back(new global_logger(os));
	}
}


void global_logger::message(const char* msg)
{
	for(auto i = loggers.begin(); i != loggers.end(); ++i)
		(*i)->os.print(msg);
}
void global_logger::message(const std::string& msg)
{
	for(auto i = loggers.begin(); i != loggers.end(); ++i)
		(*i)->os.print(msg);
}
