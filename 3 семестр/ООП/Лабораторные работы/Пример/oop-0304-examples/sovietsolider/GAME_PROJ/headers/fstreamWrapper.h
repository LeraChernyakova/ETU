#ifndef FSTREAM_WRAPPER_H
#define FSTREAM_WRAPPER_H

#include "ostreamWrapper.h"


class FstreamWrapper : public OstreamWrapper
{
	protected:

	virtual void os_open();
	virtual void os_close();

	private:

	const char* fname;

	public:

	FstreamWrapper(std::ofstream& os, const char* fname);
};

#endif