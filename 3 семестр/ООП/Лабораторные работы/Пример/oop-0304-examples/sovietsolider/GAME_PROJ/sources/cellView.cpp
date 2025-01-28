#include "../headers/cellView.h"
#include "../headers/cell.h"
CellView::CellView(char disp_char, Cell& owner) : disp_char(disp_char), owner(owner)
{
}


char CellView::get_disp_char() const
{
	if(owner.get_has_player())
		return owner.get_player().getView().get_disp_char();
	else if(owner.get_has_object())
		return owner.get_object().getView().get_disp_char();
	else if(owner.get_has_enemy())
		return owner.get_enemy().getView().get_disp_char();
	else if(owner.get_exit())
		return 'E';
	else if(owner.get_entrance())
		return 'O';
	else if(owner.isWall())
		return '@';
	return disp_char;
}