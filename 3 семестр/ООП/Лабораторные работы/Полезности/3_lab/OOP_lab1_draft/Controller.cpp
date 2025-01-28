
#include "Controller.h"


void Controller::movePlayerUp(Field &field, Player& player, Log &log) {
    PrintField print_field;
    if (!field.getCell((field.getHeight() + field.getActiveCellY() - 1) %
                       field.getHeight(), field.getActiveCellX()).getBarrier()) {
        field.moveUp(1, player, log);
    }
//    if (field.getCell((field.getHeight() + field.getActiveCellY() - 1) %
//                      field.getHeight(), field.getActiveCellX()).getBarrier())
    else
        field.getFieldObserver()->stepOnBarrier();
    print_field.print(field);
}

void Controller::movePlayerDown(Field &field, Player& player, Log &log) {
    PrintField print_field;
    if (!field.getCell((field.getHeight() + field.getActiveCellY() + 1) %
                       field.getHeight(), field.getActiveCellX()).getBarrier()) {
        field.moveDown(1, player, log);
    }
    else
        field.getFieldObserver()->stepOnBarrier();
    print_field.print(field);
}

void Controller::movePlayerRight(Field &field, Player& player, Log &log) {
    PrintField print_field;
    if (!field.getCell(field.getActiveCellY(), (field.getWidth() + field.getActiveCellX() + 1) %
                                               field.getWidth()).getBarrier()) {
        field.moveRight(1, player, log);
    }
    else
        field.getFieldObserver()->stepOnBarrier();
    print_field.print(field);
}

void Controller::movePlayerLeft(Field &field, Player& player, Log &log) {
    PrintField print_field;
    if (!field.getCell(field.getActiveCellY(), (field.getWidth() + field.getActiveCellX() - 1) %
                                               field.getWidth()).getBarrier()) {
        field.moveLeft(1, player, log);
    }
    else
        field.getFieldObserver()->stepOnBarrier();
    print_field.print(field);
}

void Controller::doubleMovePlayerUp(Field &field, Player& player, Log &log) {
    PrintField print_field;
    if (!field.getCell((field.getHeight() + field.getActiveCellY() - 2) %
                       field.getHeight(), field.getActiveCellX()).getBarrier()) {
        field.moveUp(2, player, log);
    }
    else
        field.getFieldObserver()->stepOnBarrier();
    print_field.print(field);
}

void Controller::doubleMovePlayerDown(Field &field, Player& player, Log &log) {
    PrintField print_field;
    if (!field.getCell((field.getHeight() + field.getActiveCellY() + 2) %
                       field.getHeight(), field.getActiveCellX()).getBarrier()) {
        field.moveDown(2, player, log);
    }
    else
        field.getFieldObserver()->stepOnBarrier();
    print_field.print(field);
}

void Controller::doubleMovePlayerRight(Field &field, Player& player, Log &log) {
    PrintField print_field;
    if (!field.getCell(field.getActiveCellY(), (field.getWidth() + field.getActiveCellX() + 2) %
                                               field.getWidth()).getBarrier()) {
        field.moveRight(2, player, log);
    }
    else
        field.getFieldObserver()->stepOnBarrier();
    print_field.print(field);
}

void Controller::doubleMovePlayerLeft(Field &field, Player& player, Log &log) {
    PrintField print_field;
    if (!field.getCell(field.getActiveCellY(), (field.getWidth() + field.getActiveCellX() - 2) %
                                               field.getWidth()).getBarrier()) {
        field.moveLeft(2, player, log);
    }
    else
        field.getFieldObserver()->stepOnBarrier();
    print_field.print(field);
}

void Controller::printPlayerInfo(Player &player) {
    std::cout << "Health: " << player.getHealth() << "\nProtection: " << player.getProtection() << "\nPoints: "
              << player.getPoints() << '\n';
}

void Controller::getAction(bool &game, Player &player, Field &field, CommandReader &reader, Log &log) {
    switch(reader.getDirection()){
        case Direction::UP:
            Controller::movePlayerUp(field, player, log);
            break;
        case Direction::DOWN:
            Controller::movePlayerDown(field, player, log);
            break;
        case Direction::LEFT:
            Controller::movePlayerLeft(field, player, log);
            break;
        case Direction::RIGHT:
            Controller::movePlayerRight(field, player, log);
            break;
        case Direction::DOUBLE_UP:
            Controller::doubleMovePlayerUp(field, player, log);
            break;
        case Direction::DOUBLE_DOWN:
            Controller::doubleMovePlayerDown(field, player, log);
            break;
        case Direction::DOUBLE_LEFT:
            Controller::doubleMovePlayerLeft(field, player, log);
            break;
        case Direction::DOUBLE_RIGHT:
            Controller::doubleMovePlayerRight(field, player, log);
            break;
        case Direction::EXIT:
            game = false;
            break;
        case Direction::NONE:
            break;
    }
    if (player.getDead() or player.getWin()){
        game = false;
    }
}

bool Controller::isFileLogger(CommandReader &reader) {
    return reader.getIsFileLogger();
}

bool Controller::isConsoleLogger(CommandReader &reader) {
    return reader.getIsConsoleLogger();
}

int Controller::getFieldHeight(CommandReader &reader, IGameObserver *&game_observer, Log &log) {
    int field_height = reader.getFieldHeight();
    if (field_height < 5 or field_height > 18){
        game_observer->invalidFieldHeight(log);
        field_height = 10;
    }
    return field_height;
}

int Controller::getFieldWidth(CommandReader &reader, IGameObserver *&game_observer, Log &log) {
    int field_width = reader.getFieldWidth();
    if (field_width < 5 or field_width > 18){
        game_observer->invalidFieldWidth(log);
        field_width = 10;
    }
    return field_width;
}

bool Controller::isTraceLevel(CommandReader &reader) {
    return reader.getIsTraceLevel();
}

bool Controller::isInfoLevel(CommandReader &reader) {
    return reader.getIsInfoLevel();
}

bool Controller::isErrorLevel(CommandReader &reader) {
    return reader.getIsErrorLevel();
}