#ifndef BIND_EXIT_H
#define BIND_EXIT_H
#include "bindGame.h"

class BindExit : public BindGame
{
	private:
		char symb;
	public:
		BindExit(char c);
		void do_action();
		void set_symb(char s);
		char get_symb();
};


#endif