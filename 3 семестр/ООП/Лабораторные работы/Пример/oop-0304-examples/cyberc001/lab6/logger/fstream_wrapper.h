#ifndef FSTREAM_WRAPPER_H
#define FSTREAM_WRAPPER_H

#include "ostream_wrapper.h"

class fstream_wrapper : public ostream_wrapper
{
	protected:

	virtual void os_open();
	virtual void os_close();

	private:

	const char* fname;

	public:

	fstream_wrapper(std::ofstream& os, const char* fname);
};

#endif
