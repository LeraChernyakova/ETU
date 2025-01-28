#include "class_creator.h"

#include "serializable.h"

#include <cstring>
#include "save_exceptions.h"

std::map<std::string, default_constructor_func*> class_creator::def_constructors;
std::string* class_creator::preinit_str = nullptr;
default_constructor_func** class_creator::preinit_func = nullptr;
size_t class_creator::preinit_size = 0;


void class_creator::init()
{
	for(size_t i = 0; i < preinit_size; ++i)
	{
		def_constructors[preinit_str[i]] = preinit_func[i];
	}
	std::free(preinit_str);
	std::free(preinit_func);
}

void class_creator::addDefConstructor(std::string class_name, default_constructor_func* cn)
{
	preinit_size++;
	preinit_str = (std::string*)std::realloc(preinit_str, preinit_size * sizeof(std::string));
	preinit_func = (default_constructor_func**)std::realloc(preinit_func, preinit_size * sizeof(void*));

	preinit_str[preinit_size-1] = class_name;
	preinit_func[preinit_size-1] = cn;
}
void* class_creator::loadObject(savestream& svs)
{
	std::string class_name = svs.readString();
	int backw = std::strlen(class_name.c_str()) + 1;
	svs.seekg(-backw, std::ios_base::cur);

	auto defcn = def_constructors.find(class_name);
	if(defcn == def_constructors.end())
		throw save_error_unknown_class_name(class_name);
	serializable* obj = (serializable*)(*defcn->second)();
	obj->loadFromFile(svs);
	return obj;
}
