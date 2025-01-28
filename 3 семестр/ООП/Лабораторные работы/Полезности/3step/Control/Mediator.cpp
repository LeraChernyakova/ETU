#include "Mediator.h"

void Mediator::checkParameters(Player& player, GameField& field, Factory* factory, char& lp, Instruments inst, Union union1, WinConsoleControl cons){
    checkHole(player, field, inst, union1, cons);
    checkBill(player, field, factory, inst, union1, cons);
    checkHP(player, field, lp, union1, cons);
}

void Mediator::checkHole(Player& player, GameField& field, Instruments inst, Union union1, WinConsoleControl cons){
    if (player.getHole()!=0){
        int index=0, x, y;
        while (index==0){
            x=rand() % (field.getSizeX()-1);
            y=rand() % (field.getSizeY()-1);
            if (!field.getField()[y][x].getBarrier()) index=1;
        }
        inst.changePlayer(field.getPlayerX(), field.getPlayerY(), inst, field, '*', cons);
        field.changeData(x-field.getPlayerX(), y-field.getPlayerY());
        field.doOccasions(player, union1);
        inst.changePosition(field, cons);
        player.downHole();
    }
}

void Mediator::checkBill(Player& player, GameField& field, Factory* factory, Instruments inst, Union union1, WinConsoleControl cons){
    if (player.getBill() >= 60 && !player.getExitP()) {
        factory=new ExitFactory;
        factory->createEvent()->react(player, union1);
        field.getField()[field.getSizeY()-1][field.getSizeX()-1].setOccasion(factory);
        field.getField()[field.getSizeY()-1][field.getSizeX()-1].setBarrier(false);
        inst.changePlayer(field.getSizeX()-1, field.getSizeY()-1, inst, field, '1', cons);
        player.changeExitP();
    }
}

void Mediator::checkHP(Player& player, GameField& field, char& lp, Union union1, WinConsoleControl cons){
    if ((player.getHP()==0) or
        (player.getExit()==1 and field.getPlayerY()==field.getSizeY()-1 and field.getPlayerX()==field.getSizeX()-1)) {
        union1.getSecondLevel()->react1("Win", union1.getinfo(), union1.getLog(),0);
        lp='e';
    }
}

void Mediator::move(int x_change, int y_change, GameField& field, Player& player, char& lp, Factory* factory, Instruments inst, Union union1, WinConsoleControl cons) {
    if (!field.getField()[(field.getSizeY() + field.getPlayerY() + y_change) % field.getSizeY()]
        [(field.getSizeX() + field.getPlayerX() + x_change) % field.getSizeX()].getBarrier()) {
        union1.getFirstLevel()->react(union1.getinfo(), union1.getLog(), 1);
        field.changeData(x_change, y_change);
        field.doOccasions(player, union1);
        factory=new PeacefulFactory;
        field.getField()[field.getPlayerY()][field.getPlayerX()].setOccasion(factory);
        checkParameters(player, field, factory, lp, inst, union1, cons);
    }
    else union1.getThirdLevel()->react1("Impassable cell", union1.getinfo(), union1.getLog(), 0);
}

