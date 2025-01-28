#ifndef CELL_H
#define CELL_H

#include "../cell_object.h"

#include <stdlib.h>

class field;
class cell_view;

class cell
{
	public:

	cell();
	cell(bool passable);
	~cell();

	virtual bool set_object(cell_object* obj);
	bool has_object() const;
	cell_object& get_object() const;

	cell_view& get_view();

	protected:

	virtual void init_view();

	cell_view* cv;

	private:

	bool passable;
	cell_object* obj;
};

#endif
