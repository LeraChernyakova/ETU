#include "../headers/cellObject.h"

CellObjectView& CellObject::getView()
{
	return *cv;
}


CellObject::~CellObject()
{
	delete cv;
}