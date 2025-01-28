#include "global_logger.h"

std::map<global_logger_level, std::vector<global_logger*>> global_logger::loggers;

global_logger::global_logger(ostream_wrapper& os) : os(os){}


void global_logger::init_loggers(enum global_logger_level level,
				const std::vector<std::reference_wrapper<ostream_wrapper>>& streams)
{
	for(auto i = streams.begin(); i != streams.end(); ++i){
		ostream_wrapper& os = (*i).get();
		loggers[level].push_back(new global_logger(os));
	}
}


void global_logger::message(enum global_logger_level level, const char* msg)
{
	for(auto i = loggers[level].begin(); i != loggers[level].end(); ++i)
		(*i)->os.print(msg);
}
void global_logger::message(enum global_logger_level level, const std::string& msg)
{
	for(auto i = loggers[level].begin(); i != loggers[level].end(); ++i)
		(*i)->os.print(msg);
}
