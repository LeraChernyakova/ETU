#ifndef CLASS_CREATOR_H
#define CLASS_CREATOR_H

#include <functional>
#include <map>

#include "savestream.h"

typedef std::function<void*()> default_constructor_func;

class class_creator
{
	private:

	static std::map<std::string, default_constructor_func*> def_constructors;
	static std::string* preinit_str;
	static default_constructor_func** preinit_func;
	static size_t preinit_size;


	public:

	static void init();

	static void addDefConstructor(std::string class_name, default_constructor_func* cn);
	static void* loadObject(savestream& svs);
};

#endif
