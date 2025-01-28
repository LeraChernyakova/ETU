#pragma once

#include <iostream>
#include"Player.h"
#include"Cell.h"

class Field
{
private:
	int width;
	int height;
	int player_x = 1;
	int player_y = 1;
	Cell** cells;
public:
	Field();
	Field(int width, int height, int player_x, int player_y);

	Field(const Field& obj);
	Field& operator=(const Field& obj) {
		if (this != &obj) {
			width = obj.width;
			height = obj.height;
			player_x = obj.player_x;
			player_y = obj.player_y;
			cells = new Cell * [height];
			for (int i = 0; i < height; i++) {
				cells[i] = new Cell[width];
			}
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					cells[i][j] = obj.cells[i][j];
				}

			}
		}
		return *this;
	}
	Field(Field&& obj) {
		std::swap(width, obj.width);
		std::swap(height, obj.height);
		std::swap(player_x, obj.player_x);
		std::swap(player_y, obj.player_y);
		std::swap(cells, obj.cells);
	}
	Field& operator=(Field&& obj) {
		if (this != &obj) {
			std::swap(width, obj.width);
			std::swap(height, obj.height);
			std::swap(player_x, obj.player_x);
			std::swap(player_y, obj.player_y);
			std::swap(cells, obj.cells);
		}
		return *this;
	}

	void setSize(int width_, int height_);
	int getWidth();
	int getHeight();
	
	void setPlayerY(int playerY_);
	void setPlayerX(int playerX_);
	int getPlayerX();
	int getPlayerY();

	void drawCanvas(Cell** newCells);
	Cell** getCells();
	void setCells(Cell** newCells);
};