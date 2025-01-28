#ifndef CELL_OBJECT_H
#define CELL_OBJECT_H

class cell;

class cell_object
{
	public:

	virtual char get_display(cell& holder);

	// Events
	virtual void onAdd(cell& holder);

	virtual void onPlayerPass();
	virtual void onPlayerUse();
};

#endif
