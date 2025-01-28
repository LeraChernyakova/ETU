#include "class_creator_inserter.h"

class_creator_inserter::class_creator_inserter(std::string class_name, default_constructor_func* cn)
{
	class_creator::addDefConstructor(class_name, cn);
}
