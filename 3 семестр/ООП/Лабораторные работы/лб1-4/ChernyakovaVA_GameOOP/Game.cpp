#include "Game.h"

void Game::start() {
    status = START;
    mediator->notify(this, IMediator::GAME_STATUS);
    status = INPROGRESS;
    MessageFactory::get_instance().create_message(Gamestatus, "Game is ON.");
    loop();
}

Game::Game() {
    this->player = new Player();
    this->player_view = new PlayerView(player);

    levels_gens[1] = [](Player* pl) {
        FieldGen<
            R_Player_Spawn<0, 0>,
            R_Rand_Walls<70>,
            R_Rand_Events<PlayerEventGen, 5>,
            R_Rand_Events<FieldEventGen, 5>
        > gen;
        return gen.execute(pl, 1);
    };

    levels_gens[2] = [](Player* pl) {
        FieldGen <
            R_Player_Spawn<4, 4>,
            R_Rand_Events<PlayerEventGen, 25>,
            R_Rand_Events<FieldEventGen, 5>,
            R_Column_Walls<3, 0, 5, true>,
            R_Row_Walls<3, 0, 5, false>,
            R_Column_Walls<7, 3, 6, false>,
            R_Row_Walls<4, 6, 9, false>,
            R_Column_Walls<10, 2, 4, false>,
            R_Column_Walls<7, 3, 8, false>,
            R_Column_Walls<9, 3, 6, false>,
            R_Column_Walls<11, 2, 15, false>,
            R_Column_Walls<14, 6, 14, false>,
            R_Win_Cell<13, 13>
        > gen;
        return gen.execute(pl, 2);
    };

}

void Game::reaction() {
    if (cur_step == Player::EXIT) {
        status = END;
        MessageFactory::get_instance().create_message(Gamestatus, "The player has closed the game.");
        return;
    }
    field->change_player_position(cur_step);
    is_end();
}

void Game::is_end() {
    if (player->get_coins() > 20) {
        status = WIN;
    }
    if (player->get_hearts() <= 0) {
        status = DEFEAT;
    }
    if (player->get_power() <= 0) {
        status = DEFEAT;
    }
    mediator->notify(this, IMediator::GAME_STATUS);
}

Game::STATUS Game::get_status() const {
    return status;
}

void Game::set_status(STATUS stat) {
    status = stat;
}

void Game::initialize_field(int level_num) {
    auto it = levels_gens[1];
    if (levels_gens.count(level_num) != 0) {
        it = levels_gens[level_num];
    }
    else
        MessageFactory::get_instance().create_message(Errors, "There is no such level. Level 1 has been started.");
    field = it(player);
    field_view = new FieldView(field);
    field_view->update();
}

void Game::set_step(Player::Moves cur) {
    cur_step = cur;
}

void Game::loop() {
    while (status == INPROGRESS) {
        mediator->notify(this, IMediator::STEP);
        reaction();
    }
    MessageFactory::get_instance().create_message(Gamestatus, "Game over.");
}

Game::~Game() {
    delete field_view;
    delete player_view;
    delete player;
    delete field;
}