#include "Application.h"

void Application::start() {
    Controller controller;
    CommandReader reader{};

    Field field = Field(controller.getFieldHeight(reader), controller.getFieldWidth(reader));

    FieldView print_field;
    Player player;
    field.setFieldEvents();
    print_field.printField(field);

    controller.printPlayerInfo(player);
    while (game) {
        controller.getAction(game, player, field, reader);
        print_field.printField(field);
        controller.printPlayerInfo(player);
    }
    std::cout << "\nGame over!\n";
    if (player.getWinner())
        std::cout << "YOU WIN!\n" << "You collect all resources.\n";
    else {
        std::cout << "YOU LOSE!\n";
        if (player.getFood() <= 0 && player.getHealth() > 0)
            std::cout << "You starved to death. You can try again.\n";
        else if (player.getFood() > 0 && player.getHealth() <= 0)
            std::cout << "You've lost all your health. You can try again.\n";
        else
            std::cout << "You've lost all your health and starved. You can try again.\n";
    }
   
}

Application::Application() : game(true) {}

Application::~Application() {}
