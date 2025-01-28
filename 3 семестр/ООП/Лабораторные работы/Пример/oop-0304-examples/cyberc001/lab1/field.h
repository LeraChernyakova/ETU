#ifndef FIELD_H
#define FIELD_H

#include <cstdlib>

#include "cells/cell.h"

class field
{
	public:

	field(const field& other);
	field(field&& other);
	~field();
	field& operator=(const field& other);
	field& operator=(field&& other);

	field(size_t w, size_t h);

	// Basic manipulation methods

	size_t get_w() const;
	size_t get_h() const;
	void set_size(size_t w, size_t h);

	cell& get_cell(size_t x, size_t y) const;
	void set_cell(size_t x, size_t y, cell* c);

	// Generation

	void generate_entrance_exit(size_t min_dist = 3);

	private:

	cell** cells;
	size_t cells_w, cells_h;
};

#endif
