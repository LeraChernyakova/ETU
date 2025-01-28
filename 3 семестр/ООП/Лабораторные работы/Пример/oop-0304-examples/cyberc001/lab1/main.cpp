#include <iostream>

#include "field.h"
#include "field_view.h"
#include "cells/cell_exit.h"

int main()
{
	field f(10, 10);
	field_view fv(f);

	f.generate_entrance_exit(3);
	fv.display();
}
