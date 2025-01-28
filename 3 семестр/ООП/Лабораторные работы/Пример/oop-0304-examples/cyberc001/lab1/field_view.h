#ifndef FIELD_VIEW_H
#define FIELD_VIEW_H

#include "field.h"

class field_view
{
	public:

	field_view(const field& viewf);

	void display();

	private:

	const field& viewf;
};

#endif
