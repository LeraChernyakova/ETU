#pragma once

#include "Field.h"

#include "IController.h"
#include "IControllerObserver.h"

class PlayerFacade;

class PlayerController : public IController {
public:
    PlayerController(PlayerFacade* player, int player_x = 0, int player_y = 0);
    void moveTo(int x, int y);
    void moveUp(int val = 1);
    void moveDown(int val = 1);
    void moveLeft(int val = 1);
    void moveRight(int val = 1);
    int getPositionX() const;
    int getPositionY() const;
    bool setPosition(int new_position_x, int new_position_y);
    void processCommand(const InputMessage& message) override;
    void setObserver(IControllerObserver* obs);

private:
    PlayerFacade* player;
    Field& getField();//metod
    int player_x;
    int player_y;
    IControllerObserver* observer;

};