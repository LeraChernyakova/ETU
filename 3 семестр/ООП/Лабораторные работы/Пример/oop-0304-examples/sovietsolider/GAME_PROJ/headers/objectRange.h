#ifndef OBJECT_RANGE_H
#define OBJECT_RANGE_H
#include "cellObject.h"
#include "object.h"

class ObjectRange : public Object
{
	private:
		int rangeValue = 20, pos_x = 0, pos_y = 0;
	public:
		ObjectRange();
		void addObject(Cell& holder);
		void onPass(Player& player, Field& field);
		void initView();
		void check_for_death(Field& field, std::vector <Object*>& objects, int i);
		int get_pos_x();
		int get_pos_y();
		void set_pos_x(int pos);
		void set_pos_y(int pos);
};

#endif //OBJECT_RANGE_H