#ifndef CELL_OBJECT_H
#define CELL_OBJECT_H

class cell;
class cell_object_view;

#include "save/serializable.h"

class cell_object : public serializable
{
	public:

	// Parent cell properties
	virtual bool hasParentCell() const;
	virtual cell& getParentCell() const;
	virtual void setParentCell(cell* c);

	// Display
	cell_object_view& getView();

	// Events
	virtual void onAdd(cell& holder);


	protected:

	virtual void initView();
	cell_object_view* vw;


	private:

	cell* parent_cell;
};

#endif
