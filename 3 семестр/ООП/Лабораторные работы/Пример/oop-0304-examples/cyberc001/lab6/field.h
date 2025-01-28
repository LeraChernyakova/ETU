#ifndef FIELD_H
#define FIELD_H

#include <cstdlib>

#include "cells/cell_entrance.h"
#include "logger/observable.h"
#include "save/serializable.h"

class actor;

class field : public serializable
{
	public:

	field(const field& other);
	field(field&& other);
	~field();
	field& operator=(const field& other);
	field& operator=(field&& other);

	field(size_t w = 0, size_t h = 0);

	// Basic manipulation methods

	size_t get_w() const;
	size_t get_h() const;
	void set_size(size_t w, size_t h);

	cell& get_cell(size_t x, size_t y) const;
	void set_cell(size_t x, size_t y, cell* c);

	// Generation

	cell_entrance* generate_entrance_exit(size_t min_dist = 3);

	// Gamesim

	void tickActors();

	// Serialization

	cell_object* scan_for_object(std::string class_name);
	std::vector<actor*> scan_for_actors();

	virtual std::string getClassName();
	virtual void saveToFile(savestream& svs);
	virtual void loadFromFile(savestream& svs);


	private:

	cell** cells;
	size_t cells_w, cells_h;
};

#endif
