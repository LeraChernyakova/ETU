#include "Instruments.h"

    void Instruments::drawField(int x_start, int y_start, GameField& field, WinConsoleControl cons){
        for(int i=0; i<y_start; i++){
            for(int j=0; j<x_start ; j++) {
                cons.gotoxy(j, i);
                if (field.getField()[i][j].getBarrier())
                    std::cout << 'B';
                else if (dynamic_cast<Enemy*>(field.getField()[i][j].getOccasion()))
                        std::cout<<'E';
                else if (dynamic_cast<Money*>(field.getField()[i][j].getOccasion()))
                        std::cout<<'M';
                else if (dynamic_cast<Holl*>(field.getField()[i][j].getOccasion()))
                    std::cout<<'H';
                else std::cout<<'*';
            }
        }
        cons.gotoxy(field.getSizeX()-1, field.getSizeY()-1);
        std::cout<<'0';
    }

    void Instruments::drawEvents(GameField& field, Factory* factory) {
        factory=new PeacefulFactory;
        for (int i=0;i<field.getSizeY();i++){
            for (int j=0;j<field.getSizeX();j++) {
                field.getField()[i][j].setOccasion(factory);
            }
        }
        int max = std::max(field.getSizeX(), field.getSizeY());
                for (int i = 0; i < max/1.5; i++) {
                    field.getField()[rand() % (field.getSizeY()-2)+1][rand() % (field.getSizeX()-2)+1].setBarrier(true);
                    factory=new EnemyFactory;
                    field.getField()[rand() % field.getSizeY()][rand() % field.getSizeX()].setOccasion(factory);
                    factory=new MoneyFactory;
                    field.getField()[rand() % field.getSizeY()][rand() % field.getSizeX()].setOccasion(factory);
                    factory=new HoleFactory;
                    field.getField()[rand() % field.getSizeY()][rand() % field.getSizeX()].setOccasion(factory);
                }
        field.getField()[field.getSizeY()-1][field.getSizeX()-1].setBarrier(true);
        factory=new PeacefulFactory;
        field.getField()[field.getSizeY()-1][field.getSizeX()-1].setOccasion(factory);
        }

        void Instruments::showBill(Player& player, GameField field, WinConsoleControl cons){
        cons.gotoxy(field.getSizeX()+10, 5);
        std::cout<<"Bill: "<<player.getBill();
        cons.gotoxy(field.getSizeX()+10, 6);
        std::cout<<"Health: "<<player.getHP();
        cons.gotoxy(field.getSizeX()+10, 7);
        std::cout<<"Strength: "<<player.getStrength();
        }

    void Instruments::changePlayer(int x, int y, Instruments inst, GameField& field, char object, WinConsoleControl cons) {
        cons.gotoxy(x, y);
        std::cout << object;
    }

    void Instruments::changePosition(GameField field, WinConsoleControl cons) {
        cons.gotoxy(field.getPlayerX(), field.getPlayerY());
        std::cout << "7";
    }




