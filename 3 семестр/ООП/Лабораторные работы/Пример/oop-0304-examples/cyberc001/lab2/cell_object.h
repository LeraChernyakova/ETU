#ifndef CELL_OBJECT_H
#define CELL_OBJECT_H

class cell;
class cell_object_view;

class cell_object
{
	public:

	// Parent cell properties
	virtual bool hasParentCell();
	virtual cell& getParentCell();
	virtual void setParentCell(cell* c);

	// Display
	cell_object_view& getView();

	// Events
	virtual void onAdd(cell& holder) = 0;


	protected:

	virtual void initView();
	cell_object_view* vw;


	private:

	cell* parent_cell;
};

#endif
