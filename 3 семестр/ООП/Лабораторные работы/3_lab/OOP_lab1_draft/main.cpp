#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Events/Event.h"
#include "Objects/Cell.h"
#include "Objects/Player.h"
#include "Objects/Field.h"
#include "View/PrintField.h"
#include "Controller.h"
#include "CommandReader.h"
#include "Factory/Factory.h"
#include "Application.h"



int main() {
//    int field_height, field_width;
//    std::cout << "Enter field height:";
//    std::cin >> field_height;
//    std::cout << "Enter field width:";
//    std::cin >> field_width;
//    Field field;
//    if (field_width < 3 or field_height < 3 or field_width > 11 or field_height > 11) {
//        field = Field();
//    }
//    else{
//        field = Field(field_height, field_width);
//    }
//
//    PrintField print_field;
//    Player player;
//    Mediator mediator;
//    field.setFieldEvents();
//    print_field.print(field);
//
//    std::cout << "Health: " << player.getHealth() << "\nProtection: " << player.getProtection() << "\nPoints: "
//              << player.getPoints() << '\n';
////    srand(static_cast<unsigned int>(time(0)));
//    char op = 'l';
//    do {
//        if (kbhit()) {
//            op = getch();
//
//            switch (op) {
//                case 'w':
//                case 'W':
////                    field.moveUp();
//                    mediator.movePlayerUp(field, player);
//                    break;
//
//                case 's':
//                case 'S':
//                    mediator.movePlayerDown(field, player);
//                    break;
//
//                case 'a':
//                case 'A':
//                    mediator.movePlayerLeft(field, player);
//                    break;
//
//                case 'd':
//                case 'D':
//                    mediator.movePlayerRight(field, player);
//                    break;
//                case 't':
//                case 'T':
//                    mediator.doubleMovePlayerUp(field, player);
//                    break;
//                case 'g':
//                case 'G':
//                    mediator.doubleMovePlayerDown(field, player);
//                    break;
//                case 'h':
//                case 'H':
//                    mediator.doubleMovePlayerRight(field, player);
//                    break;
//                case 'f':
//                case 'F':
//                    mediator.doubleMovePlayerLeft(field, player);
//                    break;
//            }
//            std::cout << "Health: " << player.getHealth() << "\nProtection: " << player.getProtection() << "\nPoints: "
//                      << player.getPoints() << '\n';
//        }
//
//    } while (op != 'e' and !player.getDead() and !player.getWin());
    Application application;
    application.start();
    return 0;
}
