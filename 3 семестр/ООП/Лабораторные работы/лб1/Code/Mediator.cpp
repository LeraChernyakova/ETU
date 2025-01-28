#include "Mediator.h"

void Mediator::gameProcessing() {

	state.setComand(command.readComand());
	state.commandProccesing();


	while (!state.getStatusGame())
	{
		Player player = state.getPlayer();
		Field field = state.getField();
		FieldView fieldView = state.getFieldView();
		Cell** newCells = field.getCells();


		newCells = new Cell * [field.getHeight()];
		for (int i = 0; i < field.getHeight(); i++) {
			newCells[i] = new Cell[field.getWidth()];
		}
		field.drawCanvas(newCells);
		field.setCells(newCells);
		state.setField(field);


		fieldView.setField(field);
		fieldView.drawField();


		state.setComand(command.readComand());
		state.commandProccesing();


		for (int i = 0; i < field.getHeight(); i++) {
			delete[] newCells[i];
		}
		delete[] newCells;

	}
	std::cout << "game over" << '\n';
}