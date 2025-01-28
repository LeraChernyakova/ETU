#ifndef OBJECT_H
#define OBJECT_H
#include "cellObject.h"
#include <vector>
class Object : public CellObject
{
	public:
		virtual void onPass(Player& player, Field& field) = 0;
		virtual void check_for_death(Field& field, std::vector <Object*>& objects, int i) = 0;

		virtual int get_pos_x() = 0;
		virtual int get_pos_y() = 0;
		virtual void set_pos_x(int pos) = 0;
		virtual void set_pos_y(int pos) = 0;
};

#endif
