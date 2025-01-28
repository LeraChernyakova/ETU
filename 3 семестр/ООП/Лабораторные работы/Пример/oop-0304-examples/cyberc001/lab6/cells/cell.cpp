#include "cell.h"
#include "cell_view.h"

#include "../field.h"

#include "../save/class_creator_inserter.h"

cell::cell() : passable(false), obj(nullptr), cv(nullptr){}
cell::cell(field* parf, size_t x, size_t y, bool passable) : parf(parf), x(x), y(y), passable(passable), obj(nullptr), cv(nullptr){}
cell::~cell() { if(obj) delete obj; }


bool cell::set_object(cell_object* obj)
{
	if(passable){
		if(this->obj != nullptr)
			this->obj->setParentCell(nullptr);

		this->obj = obj;
		if(obj != nullptr)
			obj->setParentCell(this);
	}
	else
		return false;
	return true;
}
bool cell::has_object() const
{
	return obj != nullptr;
}
cell_object& cell::get_object() const
{
	return *obj;
}

bool cell::is_passable() { return passable; }

// properties on a field
size_t cell::get_x() const { return x; }
size_t cell::get_y() const { return y; }
field& cell::get_parent_field() { return *parf; }
void cell::set_parent_field(field* parf) { this->parf = parf; }

// display properties
cell_view& cell::get_view()
{
	if(!cv)
		init_view();
	return *cv;
}

// utility methods
std::vector<cell*> cell::get_neighbour_cells(size_t dist) const
{
	std::vector<cell*> ret;
	for(size_t _x = (x >= dist ? x - dist : 0);
	    _x < (x + dist < parf->get_w() ? x + dist : parf->get_w());
	    ++_x)
	{
		for(size_t _y = (y >= dist ? y - dist : 0);
		    _y < (y + dist < parf->get_h() ? y + dist : parf->get_h()-1);
		    ++_y)
		{
			if(_x == x && _y == y) continue;
			ret.push_back(&parf->get_cell(_x, _y));
		}
	}
	return ret;
}
size_t cell::get_distance(cell& other) const
{
	size_t dx = get_x() > other.get_x() ? get_x() - other.get_x() : other.get_x() - get_x();
	size_t dy = get_y() > other.get_y() ? get_y() - other.get_y() : other.get_y() - get_y();
	return dx + dy;
}


void cell::init_view()
{
	cv = new cell_view(' ', *this);
}


// serialization
static default_constructor_func dcf = [](){ return new cell(); };
static class_creator_inserter cci("cell", &dcf);
std::string cell::getClassName(){ return "cell"; }
void cell::saveToFile(savestream& svs)
{
	serializable::saveToFile(svs);
	svs.writeBytes(&x, sizeof(x));
	svs.writeBytes(&y, sizeof(y));
	svs.writeBytes(&passable, sizeof(passable));

	bool has_obj = has_object();
	svs.writeBytes(&has_obj, sizeof(has_obj));
	if(obj)
		obj->saveToFile(svs);
}
void cell::loadFromFile(savestream& svs)
{
	serializable::loadFromFile(svs);
	svs.readBytes(&x, sizeof(x));
	svs.readBytes(&y, sizeof(y));
	svs.readBytes(&passable, sizeof(passable));

	bool has_obj;
	svs.readBytes(&has_obj, sizeof(has_obj));
	if(has_obj){
		obj = (cell_object*)class_creator::loadObject(svs);
		set_object(obj);
	}
}
