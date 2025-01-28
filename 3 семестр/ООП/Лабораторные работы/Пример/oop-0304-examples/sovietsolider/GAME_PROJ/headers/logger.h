#include <ostream>
#include <iostream>
#include <vector>
#include <functional>
#include "ostreamWrapper.h"
#include "cellObject.h"
#include "enemy.h"

class Logger
{
	private:
		std::vector<std::reference_wrapper<OstreamWrapper>> oslist;
		static Logger* globalLogger;
	public:
		Logger(OstreamWrapper& os);
		Logger(const std::vector<std::reference_wrapper<OstreamWrapper>>& streams);
		~Logger();

		void display(const Player& player, const std::string& prefix);
		void display(const Enemy& enemy, const std::string& prefix);
		void display(const std::string& str);

		static void initGlobal(const std::vector<std::reference_wrapper<OstreamWrapper>>& streams);
		static Logger& getGlobal();

		
		
	
	
	
};