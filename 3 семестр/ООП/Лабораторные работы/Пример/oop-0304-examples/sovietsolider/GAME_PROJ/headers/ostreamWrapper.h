#ifndef OSTREAM_WRAPPER
#define OSTREAM_WRAPPER

#include <fstream>

class OstreamWrapper
{
	protected:
		std::ostream& os;

	virtual void os_open();
	virtual void os_close();

	private:
		bool os_closed;
		int link_cnt;
	
	public:
		OstreamWrapper(std::ostream& os);
		virtual ~OstreamWrapper();


		void link();
		void unlink();

		virtual void print(const char* message);
		virtual void print(const std::string& message);
};

#endif