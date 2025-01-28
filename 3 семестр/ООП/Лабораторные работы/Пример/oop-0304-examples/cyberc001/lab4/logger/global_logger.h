#ifndef GLOBAL_LOGGER_H
#define GLOBAL_LOGGER_H

#include <functional>
#include <iostream>
#include <vector>

#include "ostream_wrapper.h"

class global_logger
{
	private:

	ostream_wrapper& os;

	global_logger(ostream_wrapper& os);

	static std::vector<global_logger*> loggers;


	public:

	static void init_loggers(const std::vector<std::reference_wrapper<ostream_wrapper>>& streams);

	static void message(const char* msg);
	static void message(const std::string& msg);
};

#endif
