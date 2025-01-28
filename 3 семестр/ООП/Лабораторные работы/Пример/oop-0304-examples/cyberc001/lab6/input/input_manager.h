#ifndef INPUT_MANAGER_H
#define IMPUT_MANAGER_H

#include <string>

class input_manager
{
	public:

	input_manager();
	~input_manager();

	int get_key_input();
	std::string get_line();
};

#endif
