#include "Controller.h"

void Controller::movePlayerUp(Field& field, Player& player) {
    FieldView print_field;
    if (!field.getCell((field.getHeight() + field.getCellY() - 1) % field.getHeight(), field.getCellX()).getBarrier()) {
        field.moveUp(1, player);
    }
    print_field.printField(field);
}

void Controller::movePlayerDown(Field& field, Player& player) {
    FieldView print_field;
    if (!field.getCell((field.getHeight() + field.getCellY() + 1) % field.getHeight(), field.getCellX()).getBarrier()) {
        field.moveDown(1, player);
    }
    print_field.printField(field);
}

void Controller::movePlayerRight(Field& field, Player& player) {
    FieldView print_field;
    if (!field.getCell(field.getCellY(), (field.getWidth() + field.getCellX() + 1) % field.getWidth()).getBarrier()) {
        field.moveRight(1, player);
    }
    print_field.printField(field);
}

void Controller::movePlayerLeft(Field& field, Player& player) {
    FieldView print_field;
    if (!field.getCell(field.getCellY(), (field.getWidth() + field.getCellX() - 1) % field.getWidth()).getBarrier()) {
        field.moveLeft(1, player);
    }
    print_field.printField(field);
}

void Controller::printPlayerInfo(Player& player) {
    std::cout << "Health: " << player.getHealth() << "\nFood: " << player.getFood() << "\nResource: "
        << player.getResource() << "\nScore: " << player.getScore()<< "\n";
}

void Controller::getAction(bool& game, Player& player, Field& field, CommandReader& reader) {
    switch (reader.getDirection()) {
    case Direction::UP:
        Controller::movePlayerUp(field, player);
        break;
    case Direction::DOWN:
        Controller::movePlayerDown(field, player);
        break;
    case Direction::LEFT:
        Controller::movePlayerLeft(field, player);
        break;
    case Direction::RIGHT:
        Controller::movePlayerRight(field, player);
        break;
    case Direction::EXIT:
        game = false;
        break;
    case Direction::NONE:
        break;
    }
    if (player.getDead() or player.getWinner()) {
        game = false;
    }
}

int Controller::getFieldHeight(CommandReader& reader) {
    int field_height = reader.getFieldHeight();
    if (field_height < 5) {
        field_height = 10;
    }
    return field_height;
}

int Controller::getFieldWidth(CommandReader& reader) {
    int field_width = reader.getFieldWidth();
    if (field_width < 5) {
        field_width = 10;
    }
    return field_width;
}

