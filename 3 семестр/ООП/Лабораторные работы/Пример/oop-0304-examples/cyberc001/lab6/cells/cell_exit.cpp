#include "cell_exit.h"
#include "cell_view.h"

#include "../save/class_creator_inserter.h"

cell_exit::cell_exit(field* parf, size_t x, size_t y, bool passable) : cell(parf, x, y, passable) {}

void cell_exit::init_view()
{
	cv = new cell_view(']', *this);
}

// serialization
static default_constructor_func dcf = [](){ return new cell_exit(); };
static class_creator_inserter cci("cell_exit", &dcf);
std::string cell_exit::getClassName(){ return "cell_exit"; }
