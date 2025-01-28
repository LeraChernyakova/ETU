#ifndef CELL_H
#define CELL_H

#include "../cell_object.h"

#include "../save/serializable.h"

#include <cstdlib>
#include <vector>

class field;
class cell_view;

class cell : public serializable
{
	public:

	cell();
	cell(field* parf, size_t x, size_t y, bool passable);
	~cell();

	// contained object properties
	virtual bool set_object(cell_object* obj);
	bool has_object() const;
	cell_object& get_object() const;

	bool is_passable();
	// properties on a field
	size_t get_x() const; size_t get_y() const;
	field& get_parent_field();
	void set_parent_field(field* parf);

	// display properties
	cell_view& get_view();

	// utility methods
	size_t get_distance(cell& other) const;
	std::vector<cell*> get_neighbour_cells(size_t dist = 1) const;

	// serialization
	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	protected:

	virtual void init_view();
	cell_view* cv;

	private:

	size_t x, y;
	field* parf;
	bool passable;
	cell_object* obj;
};

#endif
