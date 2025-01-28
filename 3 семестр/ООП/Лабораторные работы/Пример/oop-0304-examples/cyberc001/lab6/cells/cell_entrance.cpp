#include "cell_entrance.h"
#include "cell_view.h"

#include "../save/class_creator_inserter.h"

cell_entrance::cell_entrance(field* parf, size_t x, size_t y, bool passable) : cell(parf, x, y, passable){}

void cell_entrance::init_view()
{
	cv = new cell_view('[', *this);
}

// serialization
static default_constructor_func dcf = [](){ return new cell_entrance(); };
static class_creator_inserter cci("cell_entrance", &dcf);
std::string cell_entrance::getClassName(){ return "cell_entrance"; }
