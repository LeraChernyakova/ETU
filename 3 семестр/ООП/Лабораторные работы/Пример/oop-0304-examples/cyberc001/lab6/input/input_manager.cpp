#include "input_manager.h"

#include <sstream>

#include <cstdio>
#include <termios.h>
#include <unistd.h>

static void change_terminal_icanon(bool set)
{
	static struct termios told, tnew;
	tcgetattr(STDIN_FILENO, &told);
	tnew = told;
	if(set)
		tnew.c_lflag |= ICANON;
	else
		tnew.c_lflag &= ~ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &tnew);
}

input_manager::input_manager()
{
	change_terminal_icanon(false);
}
input_manager::~input_manager()
{
	change_terminal_icanon(true);
}

static inline char add_char_to_int(int& i, char c)
{
	i *= 256; i += c;
	return c;
}
int input_manager::get_key_input()
{
	int key = 0;
	if( (key = getchar()) == '\033'){
		if(add_char_to_int(key, getchar()) == '[')
			add_char_to_int(key, getchar());
	}
	return key;
}
std::string input_manager::get_line()
{
	std::stringstream ss;
	char key;
	while( (key = getchar()) != '\n')
		ss << key;
	return ss.str();
}
