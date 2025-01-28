#include "Applications.h"
#include "KeyboardReader.h"
#include "Logger.h"
#include <iostream>
#include "LogInit.h"
#include "FileReader.h"
#include <windows.h>
#include "LevelGenerator.h"
#include "FieldGenerator.h"
#include "FrameGenerator.h"
#include "CellChanger.h"
#include "Random.h"
#include "EllipseGenerator.h"
#include "LineGenerator.h"
#include "PointGenerator.h"
#include "RandomGenerator.h"
#include "PlusGenerator.h"

Applications::Applications() : playing_flag(false), field(nullptr), player(nullptr), game_controller(*this),
game_observer(this),
player_observer(&game_observer) {}
void Applications::start() {

    LevelGenerator generator{};
    int level;
    std::cout << "Enter the level: 0 - simple, 1 - hard\n";
    std::cin >> level;
    if (level == 0) {
        auto field_generator = new FieldGenerator<25, 15, PointGenerator<0, 0, CellChanger<CellType::Player>>,
            PointGenerator<5, 5, CellChanger<CellType::Door >>,
            RandomGenerator<1, CellChanger<CellType::Key >>,
            FrameGenerator<2, 2, 1, CellChanger<CellType::Water, Random<80>>>,
            EllipseGenerator<4, 4, 2, 3, CellChanger<CellType::Bomb, Random<30>>>,
            LineGenerator<0,
            0,
            5,
            5,
            CellChanger<CellType::Teleport, Random<60>>>,
            PlusGenerator<CellChanger<CellType::MapChange, Random<30>>>,
            CircleGenerator<5, 5, 3, CellChanger<CellType::Wall, Random<50>>>,
            RandomGenerator<40, CellChanger<CellType::Wall>>
        >;
        generator.setGenerator(field_generator);
    }
    else if (level == 1) {
        auto field_generator = new FieldGenerator<35, 25, PointGenerator<0, 0, CellChanger<CellType::Player>>,
            PointGenerator<5, 5, CellChanger<CellType::Door >>,
            RandomGenerator<1, CellChanger<CellType::Key >>,
            FrameGenerator<2, 2, 2, CellChanger<CellType::Water, Random<60>>>,
            EllipseGenerator<15,
            12,
            10,
            3,
            CellChanger<CellType::Bomb, Random<90>>>,
            RandomGenerator<50, CellChanger<CellType::Bomb >>,
            LineGenerator<0,
            0,
            5,
            5,
            CellChanger<CellType::Teleport, Random<80>>>,
            PlusGenerator<CellChanger<CellType::MapChange, Random<30>>>,
            CircleGenerator<5, 5, 3, CellChanger<CellType::Wall, Random<80>>>,
            RandomGenerator<50, CellChanger<CellType::Wall>>
        >;
        generator.setGenerator(field_generator);
    }

    auto out = generator.makeField();
    field = out.field;
    player = out.player;
    LogInit::start();
    KeyboardReader reader(&mediator);
    mediator.addReader(&reader);
    mediator.addController(&game_controller);
    mediator.addController(&player->getController());
    std::string flag;
    std::cout << "Do you want to set your control from a file or use the default commands?\n";
    std::cout << "If yes - press 1, otherwise press any key\n";
    std::cin >> flag;
    system("cls");
    if (flag == "1") {
        FileReader file("filetest.txt");
        ControlScheme scheme{ file.getScheme() };
        reader.setScheme(scheme);
    }
    else {
        FileReader file;
        ControlScheme scheme{ file.getScheme() };
        reader.setScheme(scheme);
    }
    playing_flag = true;
    system("cls");
    Logger::getInstance().setOffset(field->getField().getHeight() + 1);
    field->getField().setCellActive(0, 0, true);/////////////////////////////
    pf.printField(field->getField());
    player->getPlayer().setObserver(&player_observer);
    player->getController().setObserver(&cont_observer);
    field_observer.setPrintField(&pf);
    field->getField().setObserver(&field_observer);
    Logger::getInstance() << LogMessage{ "Application started", Logger::Info };
    while (playing_flag) {
        mediator.tick();
        Sleep(200);
    }
}

void Applications::stop() {
    Logger::getInstance() << LogMessage{ "Application stopped", Logger::Info };
    playing_flag = false;
}
void Applications::save() {
    Logger::getInstance() << LogMessage{ "Game id saved", Logger::Info };
    controller.save(field->getField(), player->getPlayer(), player->getController());
}
void Applications::load() {
    auto pair = controller.load();
    if (pair.first == nullptr || pair.second == nullptr) {
        return;
    }
    Logger::getInstance() << LogMessage{ "Game is loaded", Logger::Info };
    mediator.removeController(&player->getController());
    delete player;
    delete field;
    field = pair.first;
    player = pair.second;
    field->getField().setObserver(&field_observer);
    player->getPlayer().setObserver(&player_observer);
    player->getController().setObserver(&cont_observer);
    pf.printField(field->getField());
    mediator.addController(&player->getController());

}