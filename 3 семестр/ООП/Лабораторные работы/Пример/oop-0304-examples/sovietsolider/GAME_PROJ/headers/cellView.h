#ifndef CELLVIEW_H
#define CELLVIEW_H

class Cell;

class CellView
{
	public:
		CellView(char disp_char, Cell& owner);

		char get_disp_char() const;

	private:
		char disp_char;
		Cell& owner;
};

#endif