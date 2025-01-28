
#include "Application.h"


void Application::start() {
    Controller controller;
    CommandReader reader{};

    Log log = Log(controller.chooseLevel(reader), controller.isFileLogger(reader), controller.isConsoleLogger(reader));

    game_observer->gameStarted(log);

    Field field = Field(controller.getFieldHeight(reader, game_observer, log), controller.getFieldWidth(reader, game_observer, log));

    PrintField print_field;
    Player player;
    field.setFieldEvents();
    print_field.print(field);

    controller.printPlayerInfo(player);
    while (game) {
        controller.getAction(game, player, field, reader, log);
        print_field.print(field);
        controller.printPlayerInfo(player);
    }
    game_observer->gameEnded(log);
}

Application::Application() : game(true) {
    game_observer = new GameObserver;
}

Application::~Application() {
    delete game_observer;
}
