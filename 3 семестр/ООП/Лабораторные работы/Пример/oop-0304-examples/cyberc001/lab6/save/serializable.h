#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "savestream.h"

class serializable
{
	public:

	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);
};

#endif
