#include "StateGame.h"
#include<iostream>

void StateGame::setComand(std::string newCommand) {
	command = newCommand;
}

Field StateGame::getField() {
	return canvas;
}

void StateGame::setField(Field field) {
	this->canvas = field;
}

bool StateGame::getStatusGame() {
	return game_over;
}

Player StateGame::getPlayer() {
	return player;
}
void StateGame::setPlayer(Player player_) {
	player = player_;
}
void StateGame::commandProccesing() {
	if (command == "start") {
		game_over = false;

	}
	if (command == "cleanScreen") {
		std::system("cls");
	}
	if (command == "size") {
		int my_width, my_height;
		std::cout << "width = ";
		std::cin >> my_width;
		std::cout << "height = ";
		std::cin >> my_height;
		if (my_width > 0 && my_height > 0)
			canvas.setSize(my_width + 2, my_height + 2);
		else {
			canvas.setSize(30, 20);
		}
		canvas.setPlayerX(1);
		canvas.setPlayerY(1);
	}

	if (command == "end") {
		game_over = true;
	}
	if (command == "w") {
		int y = canvas.getPlayerY();
		if (canvas.getPlayerY() == 1) {
			y = canvas.getHeight() - 1;
		}
		if (canvas.getCells()[canvas.getPlayerY() - 1][canvas.getPlayerX()].getPatency())
			canvas.setPlayerY(--y);
		else {
			canvas.setPlayerY(y);
		}
		std::system("cls");
	}
	if (command == "s") {
		int y = canvas.getPlayerY();
		if (canvas.getPlayerY() >= canvas.getHeight() - 2) {
			y = 0;
		}
		if (canvas.getCells()[canvas.getPlayerY() + 1][canvas.getPlayerX()].getPatency())
			canvas.setPlayerY(++y);
		else {
			canvas.setPlayerY(y);
		}
		std::system("cls");
	}
	if (command == "a") {
		int x = canvas.getPlayerX();
		if (canvas.getPlayerX() <= 1) {
			x = canvas.getWidth() - 1;
		}
		if (canvas.getCells()[canvas.getPlayerY()][canvas.getPlayerX() - 1].getPatency())
			canvas.setPlayerX(--x);
		else {
			canvas.setPlayerX(x);
		}
		std::system("cls");
	}
	if (command == "d") {
		int x = canvas.getPlayerX();
		if (canvas.getPlayerX() >= canvas.getWidth() - 2) {
			x = 0;
		}
		if (canvas.getCells()[canvas.getPlayerY()][canvas.getPlayerX() + 1].getPatency())
			canvas.setPlayerX(++x);
		else {
			canvas.setPlayerX(x);
		}
		std::system("cls");
	}
	if (command == "info") {
		std::cout << "health = " << player.getHealth() << "\n";
		std::cout << "food = " << player.getFood() << "\n";
		std::cout << "resource = " << player.getResource() << "\n";
	}
}

FieldView StateGame::getFieldView() {
	return drawField;
}