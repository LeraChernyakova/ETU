#include "Field.h"
#include "Cell.h"


Field::Field() {
	width = 30;
	height = 20;
	player_x = 1;
	player_y = 1;
	cells = new Cell * [height];
	for (int i = 0; i < height; i++) {
		cells[i] = new Cell[width];
	}
}
Field::Field(int width = 30, int height = 20, int palyer_x = 1, int player_y = 1)
	:width(width), height(height), player_x(player_x), player_y(player_y) {
	cells = new Cell * [height];
	for (int i = 0; i < height; i++) {
		cells[i] = new Cell[width];
	}

}

Field::Field(const Field& obj) {
	width = obj.width;
	height = obj.height;
	player_x = obj.player_x;
	player_y = obj.player_y;


}

void Field::setSize(int width_, int height_) {
	width = width_;
	height = height_;
}
int Field::getWidth() {
	return width;
}

int Field::getHeight() {
	return height;
}

int Field::getPlayerX() {
	return player_x;
}
int Field::getPlayerY() {
	return player_y;
}
void Field::setPlayerY(int playerY_) {
	player_y = playerY_;
}

void Field::setPlayerX(int playerX_) {
	player_x = playerX_;
}


void Field::drawCanvas(Cell** newCells) {
	for (int i = 0; i < width; i++) {
		newCells[0][i].setType("border");//граница карты
	}
	for (int i = 1; i < height - 1; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				newCells[i][j].setType("border");
			}
			else {
				if (!(player_x == j && player_y == i)) {
					newCells[i][j].setType("nothing");
				}
				else {
					newCells[i][j].setType("hero");
				}
			}
		}
	}
	for (int i = 0; i < width; i++) {
		newCells[height - 1][i].setType("border");
	}
	newCells[10][10].setPatency(false);
	newCells[10][10].setType("rock");
}

Cell** Field::getCells() {
	return cells;
}
void Field::setCells(Cell** newCells) {
	cells = newCells;
}
