#pragma once
#include "FieldView.h"
#include <iostream>

class StateGame{
private:
	bool game_over;
	Field canvas;
	std::string command;
	Player player;
	FieldView drawField;
public:
	void setComand(std::string newCommand);
	Field getField();
	void setField(Field field);
	bool getStatusGame();
	Player getPlayer();
	void setPlayer(Player player_);
	void commandProccesing();
	FieldView getFieldView();

};