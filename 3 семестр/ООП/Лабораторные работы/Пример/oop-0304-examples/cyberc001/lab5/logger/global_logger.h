#ifndef GLOBAL_LOGGER_H
#define GLOBAL_LOGGER_H

#include <functional>
#include <iostream>
#include <vector>
#include <map>

#include "ostream_wrapper.h"

enum global_logger_level
{
	GLOGGER_LEVEL_UI,
	GLOGGER_LEVEL_EVENT
};

class global_logger
{
	private:

	ostream_wrapper& os;

	global_logger(ostream_wrapper& os);

	static std::map<global_logger_level, std::vector<global_logger*>> loggers;


	public:

	static void init_loggers(enum global_logger_level level,
				const std::vector<std::reference_wrapper<ostream_wrapper>>& streams);

	static void message(enum global_logger_level level, const char* msg);
	static void message(enum global_logger_level level, const std::string& msg);
};

#endif
