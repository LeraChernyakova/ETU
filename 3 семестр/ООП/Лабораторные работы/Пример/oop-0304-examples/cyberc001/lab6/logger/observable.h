#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "observer.h"

class observable
{
	private:

	observer* ob = nullptr;


	public:

	void setObserver(observer& ob);
	void notifyObserver();
};

#endif
