#ifndef CELLOBJECT_H
#define CELLOBJECT_H
#include "cellObjectView.h"
#include <string>
#include <sstream>
class Cell; class Player; class Field;

class CellObject
{
	public:
		virtual void initView() = 0;
		virtual ~CellObject();
		CellObjectView& getView();
	protected:
		CellObjectView* cv;
};

#endif // CELLOBJECT_H
