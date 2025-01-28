#include "cell.h"
#include "cell_view.h"
#include <iostream>

cell::cell() : passable(false), obj(nullptr)
{}
cell::cell(bool passable) : passable(passable)
{}
cell::~cell() { if(obj) delete obj; }


bool cell::set_object(cell_object* obj)
{
	if(passable)	this->obj = obj;
	else		return false;
	return true;
}
bool cell::has_object() const
{
	return obj;
}
cell_object& cell::get_object() const
{
	return *obj;
}

cell_view& cell::get_view()
{
	if(!cv)
		init_view();
	return *cv;
}


void cell::init_view()
{
	cv = new cell_view(' ');
}
