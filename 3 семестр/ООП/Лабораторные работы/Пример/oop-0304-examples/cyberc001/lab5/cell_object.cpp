#include "cell_object.h"

#include "cells/cell.h"
#include "cell_object_view.h"

// Parent cell properties
bool cell_object::hasParentCell() const { return parent_cell != nullptr; }
cell& cell_object::getParentCell() const { return *parent_cell; }
void cell_object::setParentCell(cell* c) { parent_cell = c; }

// Display
cell_object_view& cell_object::getView() { return *vw; }
void cell_object::initView()
{
	vw = new cell_object_view('*', *this);
}


void cell_object::onAdd(cell& holder) {}
