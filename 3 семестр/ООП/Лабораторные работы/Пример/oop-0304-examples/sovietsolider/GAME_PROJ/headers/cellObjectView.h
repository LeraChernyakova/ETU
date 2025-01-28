#ifndef CELLOBJECT_VIEW_H
#define CELLOBJECT_VIEW_H

class CellObject;

class CellObjectView
{
	public:
		CellObjectView(char disp_char, CellObject& owner);

		char get_disp_char() const;
	private:
		char disp_char;
		CellObject& owner;
};


#endif