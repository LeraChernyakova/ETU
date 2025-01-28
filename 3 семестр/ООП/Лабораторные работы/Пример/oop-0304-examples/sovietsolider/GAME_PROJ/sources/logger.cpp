#include "../headers/logger.h"
Logger* Logger::globalLogger;

Logger::Logger(OstreamWrapper& os)
{
	this->oslist.push_back(os);
	os.link();
}

Logger::Logger(const std::vector<std::reference_wrapper<OstreamWrapper>>& streams)
{
	for(auto i = streams.begin(); i != streams.end(); ++i){
		OstreamWrapper& ow = (*i);
		ow.link();
		oslist.push_back(*i);
	}
}
Logger::~Logger()
{
	for(auto i = oslist.begin(); i != oslist.end(); ++i){
		OstreamWrapper& ow = (*i);
		ow.unlink();
	}
}

void Logger::display(const Player& player, const std::string& prefix)
{
	for(auto i=0; i<oslist.size(); i++)
	{
		std::stringstream ss;
		ss << prefix << ": " << player;
		oslist[i].get().print(ss.str());
	}
}

void Logger::display(const std::string& str)
{
	for(auto i=0; i<oslist.size(); i++)
	{
		oslist[i].get().print(str);
	}
}

void Logger::display(const Enemy& enemy, const std::string& prefix)
{
	for(auto i=0; i<oslist.size(); i++)
	{
		std::stringstream ss;
		ss << prefix << ": " << enemy;
		oslist[i].get().print(ss.str());
	}
}

void Logger::initGlobal(const std::vector<std::reference_wrapper<OstreamWrapper>>& streams)
{
	globalLogger = new Logger(streams);
}

Logger& Logger::getGlobal() { return *globalLogger; }