
#ifndef OOP_LAB1_CONTROLLER_H
#define OOP_LAB1_CONTROLLER_H

#include "Objects/Field.h"
#include "View/PrintField.h"
#include "CommandReader.h"
#include "Log/Log.h"
#include "Log/Observers/IGameObserver.h"

class Controller {
public:
    int getFieldHeight(CommandReader &reader, IGameObserver *&game_observer, Log &log);
    int getFieldWidth(CommandReader &reader, IGameObserver *&game_observer, Log &log);
    bool isTraceLevel(CommandReader &reader);
    bool isInfoLevel(CommandReader &reader);
    bool isErrorLevel(CommandReader &reader);
    bool isFileLogger(CommandReader &reader);
    bool isConsoleLogger(CommandReader &reader);

    void movePlayerUp(Field& field, Player& player, Log &log);
    void movePlayerDown(Field &field, Player& player, Log &log);
    void movePlayerRight(Field &field, Player& player, Log &log);
    void movePlayerLeft(Field &field, Player& player, Log &log);

    void doubleMovePlayerUp(Field& field, Player& player, Log &log);
    void doubleMovePlayerDown(Field& field, Player& player, Log &log);
    void doubleMovePlayerRight(Field& field, Player& player, Log &log);
    void doubleMovePlayerLeft(Field& field, Player& player, Log &log);

    void getAction(bool &game, Player &player, Field &field, CommandReader &reader, Log &log);

    void printPlayerInfo(Player &player);

};


#endif //OOP_LAB1_CONTROLLER_H
